/?  310
/+  pretty-file, show-dir
::
|%
++  cats
  |=  pax=path
  ^-  tang
  =+  ark=.^(arch (cat 3 %c %y) pax)
  ?^  fil.ark
    ?:  =(%sched -:(flop pax))
      [>.^((map @da cord) (cat 3 %c %x) pax)<]~
    [leaf+(spud pax) (pretty-file .^(noun (cat 3 %c %x) pax))]
  ?-     dir.ark                                          ::  handle ambiguity
      ~
    [rose+[" " `~]^~[leaf+"~" (smyt pax)]]~
  ::
      [[@t ~] ~ ~]
    $(pax (welp pax /[p.n.dir.ark]))
  ::
      *
    =-  [palm+[": " ``~]^-]~
    :~  rose+[" " `~]^~[leaf+"*" (smyt pax)]
        `tank`(show-dir %c pax dir.ark)
    ==
  ==
++  file  .^(@t cx+/===/gen/hello/hoon)
::  ++  path-to-hoon
::    |=  pax=path
::    =+  ark=.^(arch (cat 3 %cy) pax)
::    ~&  [fil.ark dir.ark]
::    1
--
::
:-  %say
|=  [^ [arg=(list path)] ~]
=-  tang+(flop `tang`(zing -))
%+  turn  arg  cats
::=<  [%noun (cat [arg %c])]
::  =>
::    |%
::    ++  answer  3
::  ::  ++  file  .^(@t cx+/===/gen/hello/hoon)
::    --
::
