::  /?  310
::  /+  pretty-file, show-dir
::
|%
::  takes in a tape and splits into a list of tapes separated by newlines
++  line-split
  |=  input=tape  ^-  (list tape)
  =|  [line=tape lines=(list tape)]
  |-
  ?~  input
    lines
  ?:  !=(i.input `@t`10)  :: newline character
    %=  $
      input  t.input
      line   (weld line (trip i.input))
    ==
  %=  $
    line   ~
    input  t.input
    lines  (weld lines (limo line ~))
  ==
::  scans a comment line and outputs %comment
++  vulc  %+  cold  %commment
          ;~  plug  col  col
              (star prn)
              (just `@t`10)
          ==
::  scans lines ending with newline to get list of tapes
++  simp  %-  star  ;~  plug
              (star prn)
              (cold %newline (just `@t`10))
          ==
::  simp but last line doesn't need to end with newline
++  simpp  %-  star
           ;~  pose
             prn
             (cold %newline (just `@t`10))
           ==
::  takes a tape of "a"s and "b"s and gives a (list tape)
::  with all the "a" delimited by "b"s
::  ++  simp
::    ^-  rule
::    |=  =nail
::    =|  [line=tape lines=(list tape)]
::    |-
::    ?~  q.tape
::      lines
::    ?:
--
::
:-  %say
|=  [^ [arg=(list path) ~]]
:-  %noun
::  take in the file as a cord, convert to tape
=+  pax=-.arg
=/  raw=tape  (trip .^(@t %cx pax))
(scan raw simp)
::=+  eol=(just `@t`10)  ::  newline rule
::=+  broke=(scan raw (star ;~(pose eol prn)))
::(line-split raw)
::  =|  [line=tape lines=(list tape)]
::  |-
::  ?~  broke
::    lines
::  ?:  !=(i.broke `@t`10)
::    %=  $
::      line   (weld line (trip i.broke))
::      broke  t.broke
::    ==
::  %=  $
::    line   ~
::    lines  (weld lines (limo line ~))
::    broke  t.broke
::  ==
::
::  split tape into (list tape) on newlines

::  hair - position parser is at
::  nail - parser input
::  edge - parser output
::  rule - parser

::  use +lust to detect newlines
::  +lust:  (char, hair) -> hair
::
::  parse to tuple
::  +plug:  (edge, rule) -> edge
::
::  removes leading whitespace
::  +inde:  rule -> rule
::  see also +iny, seems to do the same thing?
::
::  recursive parsers
::  +knee: (noun, gate(rule)) -> rule
::
::  consumes a char, producing it as a result
::  +next: nail -> edge
::
::  add label to an edge parsed by a rule
::  +stag: (noun, rule) -> rule
::
::  parse tape or crash
::  +scan: (tape, rule) -> tape or crash
