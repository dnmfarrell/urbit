::  partial hoon parser for doccords experiments
::
/+  *doccords
:-  %say
|=  [^ [arg=(list path)] ~]
=<  noun+(parse-hoon -.arg)
::
=>  |%
    ++  stub  ~
    --
::
|%
++  parse-hoon
  |=  pax=path  ^-  hoon
  ::
  =+  raw=.^(@t %cx pax)
  ::
  (ream raw)
--
