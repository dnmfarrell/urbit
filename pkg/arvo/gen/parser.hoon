::  partial hoon parser for doccords experiments
::
/+  *doccords
::
:-  %say
|=  [^ [arg=(list path)] ~]
=<  hoon+(parse-file -.arg)
::
=>  |%
    ++  stub  ~
    --
::
|%
++  parse-file
  |=  pax=path  ^-  hoon
  ::
  =+  raw=.^(@t %cx pax)
  ::
  (ream raw)
--
