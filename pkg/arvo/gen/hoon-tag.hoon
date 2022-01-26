::  takes in hoon files and builds a data structure with
::  lines tagged as either comments or code. doesn't work
::  with lines that have both just yet
::
:-  %say
|=  [^ [arg=(list path)] ~]
=<  noun+(parse-file -.arg)
::
=>  |%
    +$  tags  ?(%comment %code)  :: tags for lines
    +$  tagl  [tags tape]  :: tagged line
    --
::
|%
++  parse-file
  |=  pax=path  ^-  (list tagl)
  ::  grabs file at path and turns it into a tape
  =+  raw=(trip .^(@t %cx pax))
  ::  splits tape at newlines and strips whitespace
  =+  clean-lines=(turn (scan raw split) (curr scan strip))
  =|  parsed-lines=(list tagl)
  |-
  ?~  clean-lines
    parsed-lines
  =+  parz=(tag-line -.clean-lines)
  %=  $
    clean-lines  +.clean-lines
    parsed-lines  (weld parsed-lines (limo parz ~))
  ==
::
++  eol  (just '\0a')  :: newline character
::
::  splits a tape into (list tape) separated by newlines
++  split  (star ;~(sfix (star prn) eol))
::
::  adds %comment label to commented line
++  coc  (stag %comment ;~(plug col col (star prn)))
::  adds %code label to line. doesn't actually check to make sure its commented
++  poc  (stag %code (star prn))
::
++  tag-line
  |=  line=tape  ^-  tagl
  ;;(tagl (scan line ?:(=(-.line ':') coc poc)))
::
::  strip leading whitespace
++  strip  ;~(pfix (star ace) (star prn))
--
