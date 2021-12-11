{-|
  `into` is a one-shot executable that sends a single command to an Urbit's
  %khan vane, and produces a single response. Commonly this response will be a
  ticket for a job to be completed out of band; this ticket can be polled for
  status or results.

  Some interesting commands supported by `into`:

  - `code`: produce the ship's current `+code`.
  - `reset`: reset the ship's `+code`.
  - `mass`: aspirationally, retrieve and dump memory usage info.
-}
module Into.Main (main) where

import            Control.Monad
import            Data.Binary.Strict.Get
import qualified  Data.ByteString as B
import            Data.ByteString.Builder
import qualified  Data.ByteString.Lazy as L
import qualified  Data.Map as M
import qualified  Data.Text as T
import            GHC.Natural
import            Network.Socket
import            Network.Socket.ByteString
import            System.Environment
import            System.FilePath.Posix
import            System.Posix
-- import            Text.Printf
import            Urbit.Noun
import            Urbit.Ob

usage :: IO ()
usage = do
  putStrLn "usage: into <pier> <cmd>"
  putStrLn "cmds:"
  mapM_ (putStrLn . ("  " ++)) $ M.keys cmds

khanVersion :: Natural
khanVersion = 0

packNoun :: ToNoun a => a -> B.ByteString
packNoun jar =
  let pac = jamBS (toNoun jar) in
  L.toStrict $ toLazyByteString $
    mconcat [ word8 0x9                               --  newt tag byte
            , word32LE $ fromIntegral $ B.length pac  --  32-bit length
            , byteString pac                          --  +jam of noun
            ]

buildFyrd :: ToNoun a => a -> B.ByteString
buildFyrd com = packNoun (Cord "fyrd", khanVersion, com)

codeCmd :: B.ByteString
codeCmd = buildFyrd (Cord "cod", False)

codeResponse :: Noun -> IO ()
codeResponse jar = do
  (res, cod') <- fromNounExn jar :: IO (Cord, Maybe Natural)
  unless ((Cord "cod") == res) $
    error $ "bad res: " ++ show res
  case cod' of
    Nothing -> error "no code"
    Just cod -> putStrLn . T.unpack . renderPatp . patp $ cod

codeResetCmd :: B.ByteString
codeResetCmd = buildFyrd (Cord "cod", True)

ackResponse :: String -> Noun -> IO ()
ackResponse msg jar = do
  zac <- fromNounExn jar
  unless ((Cord "ack") == zac) $ error $ "bad jar: " ++ show jar
  putStrLn msg

massCmd :: B.ByteString
massCmd = buildFyrd (Cord "mas", 0 :: Natural)

--            cmd,    wire cmd,     on response
cmds :: M.Map String (B.ByteString, Noun -> IO ())
cmds = M.fromList
  [ ("code",  (codeCmd,       codeResponse))
  , ("reset", (codeResetCmd,  ackResponse "+code reset."))
  , ("mass",  (massCmd,       ackResponse "|mass TODO"))
  ]
cmdFind :: String -> IO (B.ByteString, Noun -> IO ())
cmdFind nam = case M.lookup nam cmds of
  Nothing -> do { usage; error "cmd not found" }
  Just cmd -> return cmd

extractNoun :: FromNoun a => B.ByteString -> IO a
extractNoun = cueBSExn >=> fromNounExn

-- hexDumpBS :: B.ByteString -> T.Text
-- hexDumpBS = B.foldr (\b -> (<>) (T.pack $ printf "%02x" b)) ""

main :: IO ()
main = withSocketsDo $ do
  ars <- getArgs
  unless (2 == length ars) $
    do { usage; error "wrong number of arguments" }
  let [paf, nam] = ars
  (cmd, act) <- cmdFind nam
  changeWorkingDirectory paf
  soc <- socket AF_UNIX Stream 0
  connect soc (SockAddrUnix $ ".urb" </> "khan.sock")
  send soc cmd
  hedBS <- recv soc 5
  unless (9 == B.head hedBS) $ do { error "newt: bad tag" }
  let (len', _) = runGet getWord32le $ B.tail hedBS
  case len' of
    Left fal -> error fal
    Right len -> do
      wad <- recv soc $ fromIntegral len
      jar <- extractNoun wad
      act jar
  close soc
