::  chyg: whether account is (non-)change. 0 or 1
::  bytc: "btc-byts" with dat cast to @ux
|%
+$  network  ?(%main %testnet)
+$  xpub  @ta
+$  address  ?(base58-a bech32-a)
+$  base58-a  $%([%base58 cord])
+$  bech32-a  $%([%bech32 cord])
+$  fprint  [%4 @ux]
+$  bipt  $?(%44 %49 %84)
+$  chyg  $?(%0 %1)
+$  idx   @ud
+$  hdkey  [=fprint pubkey=bytc =bipt =chyg =idx]
+$  sats  @ud
+$  vbytes  @ud
+$  bytc  [wid=@ dat=@ux]
+$  hash256  [wid=%32 dat=@ux]
+$  hash160  [wid=%20 dat=@ux]
+$  hash  ?(hash256 hash160)
+$  txid  hash256
+$  rawtx  bytc
+$  buffer  (list @ux)
+$  utxo  [pos=@ =txid height=@ value=sats recvd=(unit @da)]
++  address-info
  $:  =address
      confirmed-value=sats
      unconfirmed-value=sats
      utxos=(set utxo)
  ==
++  tx
  |%
  +$  data
    $:  is=(list input)
        os=(list output) 
        locktime=@ud
        nversion=@ud
        segwit=(unit @ud)
    ==
  +$  val
    $:  =txid
        pos=@ud
        =address
        value=sats
    ==
  ::  included: whether tx is in the mempool or blockchain
  ::
  +$  info
    $:  included=?
        =txid
        confs=@ud
        recvd=(unit @da)
        inputs=(list val)
        outputs=(list val)
    ==
  +$  input
    $:  =txid
        pos=@ud
        sequence=bytc
        redeem-script=(unit bytc)
        pubkey=(unit bytc)
        value=sats
    ==
  +$  output
    $:  script-pubkey=bytc
        value=sats
    ==
  --
++  psbt
  |%
  +$  base64  cord
  +$  in  [=utxo =rawtx =hdkey]
  +$  out  [=address hk=(unit hdkey)]
  +$  target  $?(%input %output)
  +$  keyval  [key=bytc val=bytc]
  +$  map  (list keyval)
  --
++  ops
  |%
  ++  op-dup  118
  ++  op-equalverify  136
  ++  op-hash160      169
  ++  op-checksig     172
  --
--
