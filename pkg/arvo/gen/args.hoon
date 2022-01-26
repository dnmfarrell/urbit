::  =>  ~
::  :-  %say
::  |=  *
::  :-  %noun
::  +<+<-
::  :*
::    %head  +
::    %tail  -
::    %one  +<+<-
::    %two  +>
::  ==
/+  pretty-file, show-dir

:-  %say
|=  [^ arg=path vane=?(%g %c)]
=<  [%noun (bweh +6:+<+<-)]
=>
  |%
    ++  one  1
  --
|%
++  bweh
  |=  pax=path
  ^-  tang
  =+  ark=.^(arch (cat 3 vane %y) pax)
  ?^  fil.ark
    ?:  =(%sched -:(flop pax))
      [>.^((map @da cord) (cat 3 vane %x) pax)<]~
    [leaf+(spud pax) (pretty-file .^(noun (cat 3 vane %x) pax))]
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
        `tank`(show-dir vane pax dir.ark)
    ==
  ==
--
