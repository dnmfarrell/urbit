:: library with a partial hoon parser for doccords experiments
::
|%
++  ream                                                ::  parse cord to hoon
  |=  txt=@
  ^-  hoon
  (rash txt vest)
::  ::
::  ++  vest
::    ~/  %vest
::    |=  tub=nail
::    ^-  (like hoon)
::    %.  tub
::    %-  full
::    (ifix [gay gay] tall:vast)
::  ::
::  ++  vast
::    |%
::    ++  tall                                              ::  full tall form
::      %+  knee  *hoon
::      |.(~+((wart ;~(pose expression:(norm &) long lute apex:(sail &)))))
::    ++  norm
::      |=  tol=?
::      |%
::      ++  expression
::        %-  stew
::        ^.  stet  ^.  limo
::        :~  :-  '|'
::              ;~  pfix  bar
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  ['_' (rune cab %brcb exqr)]
::                    ['%' (runo cen %brcn ~ expe)]
::                    ['@' (runo pat %brpt ~ expe)]
::                    [':' (rune col %brcl expb)]
::                    ['.' (rune dot %brdt expa)]
::                    ['-' (rune hep %brhp expa)]
::                    ['^' (rune ket %brkt expx)]
::                    ['~' (rune sig %brsg exqc)]
::                    ['*' (rune tar %brtr exqc)]
::                    ['=' (rune tis %brts exqc)]
::                    ['?' (rune wut %brwt expa)]
::                    ['$' (rune buc %brbc exqe)]
::                ==
::              ==
::            :-  '$'
::              ;~  pfix  buc
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  ['@' (stag %ktcl (rune pat %bcpt exqb))]
::                    ['_' (stag %ktcl (rune cab %bccb expa))]
::                    [':' (stag %ktcl (rune col %bccl exqs))]
::                    ['%' (stag %ktcl (rune cen %bccn exqs))]
::                    ['<' (stag %ktcl (rune gal %bcgl exqb))]
::                    ['>' (stag %ktcl (rune gar %bcgr exqb))]
::                    ['|' (stag %ktcl (rune bar %bcbr exqc))]
::                    ['&' (stag %ktcl (rune pam %bcpm exqc))]
::                    ['^' (stag %ktcl (rune ket %bckt exqb))]
::                    ['~' (stag %ktcl (rune sig %bcsg exqd))]
::                    ['-' (stag %ktcl (rune hep %bchp exqb))]
::                    ['=' (stag %ktcl (rune tis %bcts exqg))]
::                    ['?' (stag %ktcl (rune wut %bcwt exqs))]
::                    ['.' (rune dot %kttr exqa)]
::                    [',' (rune com %ktcl exqa)]
::                ==
::              ==
::            :-  '%'
::              ;~  pfix  cen
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  ['_' (rune cab %cncb exph)]
::                    ['.' (rune dot %cndt expb)]
::                    ['^' (rune ket %cnkt expd)]
::                    ['+' (rune lus %cnls expc)]
::                    ['-' (rune hep %cnhp expb)]
::                    [':' (rune col %cncl expi)]
::                    ['~' (rune sig %cnsg expn)]
::                    ['*' (rune tar %cntr expm)]
::                    ['=' (rune tis %cnts exph)]
::                ==
::              ==
::            :-  ':'
::              ;~  pfix  col
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  ['_' (rune cab %clcb expb)]
::                    ['^' (rune ket %clkt expd)]
::                    ['+' (rune lus %clls expc)]
::                    ['-' (rune hep %clhp expb)]
::                    ['~' (rune sig %clsg exps)]
::                    ['*' (rune tar %cltr exps)]
::                ==
::              ==
::            :-  '.'
::              ;~  pfix  dot
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  ['+' (rune lus %dtls expa)]
::                    ['*' (rune tar %dttr expb)]
::                    ['=' (rune tis %dtts expb)]
::                    ['?' (rune wut %dtwt expa)]
::                    ['^' (rune ket %dtkt exqn)]
::                ==
::              ==
::            :-  '^'
::              ;~  pfix  ket
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  ['|' (rune bar %ktbr expa)]
::                    ['.' (rune dot %ktdt expb)]
::                    ['-' (rune hep %kthp exqc)]
::                    ['+' (rune lus %ktls expb)]
::                    ['&' (rune pam %ktpm expa)]
::                    ['~' (rune sig %ktsg expa)]
::                    ['=' (rune tis %ktts expj)]
::                    ['?' (rune wut %ktwt expa)]
::                    ['*' (rune tar %kttr exqa)]
::                    [':' (rune col %ktcl exqa)]
::                ==
::              ==
::            :-  '~'
::              ;~  pfix  sig
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  ['|' (rune bar %sgbr expb)]
::                    ['$' (rune buc %sgbc expf)]
::                    ['_' (rune cab %sgcb expb)]
::                    ['%' (rune cen %sgcn hind)]
::                    ['/' (rune fas %sgfs hine)]
::                    ['<' (rune gal %sggl hinb)]
::                    ['>' (rune gar %sggr hinb)]
::                    ['+' (rune lus %sgls hinc)]
::                    ['&' (rune pam %sgpm hinf)]
::                    ['?' (rune wut %sgwt hing)]
::                    ['=' (rune tis %sgts expb)]
::                    ['!' (rune zap %sgzp expb)]
::                ==
::              ==
::            :-  ';'
::              ;~  pfix  mic
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  [':' (rune col %mccl expi)]
::                    ['/' (rune fas %mcfs expa)]
::                    ['<' (rune gal %mcgl exp1)]
::                    ['~' (rune sig %mcsg expi)]
::                    [';' (rune mic %mcmc exqc)]
::                ==
::              ==
::            :-  '='
::              ;~  pfix  tis
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  ['|' (rune bar %tsbr exqc)]
::                    ['.' (rune dot %tsdt expq)]
::                    ['?' (rune wut %tswt expw)]
::                    ['^' (rune ket %tskt expt)]
::                    [':' (rune col %tscl expp)]
::                    ['/' (rune fas %tsfs expo)]
::                    [';' (rune mic %tsmc expo)]
::                    ['<' (rune gal %tsgl expb)]
::                    ['>' (rune gar %tsgr expb)]
::                    ['-' (rune hep %tshp expb)]
::                    ['*' (rune tar %tstr expg)]
::                    [',' (rune com %tscm expb)]
::                    ['+' (rune lus %tsls expb)]
::                    ['~' (rune sig %tssg expi)]
::                ==
::              ==
::            :-  '?'
::              ;~  pfix  wut
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  ['|' (rune bar %wtbr exps)]
::                    [':' (rune col %wtcl expc)]
::                    ['.' (rune dot %wtdt expc)]
::                    ['<' (rune gal %wtgl expb)]
::                    ['>' (rune gar %wtgr expb)]
::                    ['-' ;~(pfix hep (toad txhp))]
::                    ['^' ;~(pfix ket (toad tkkt))]
::                    ['=' ;~(pfix tis (toad txts))]
::                    ['#' ;~(pfix hax (toad txhx))]
::                    ['+' ;~(pfix lus (toad txls))]
::                    ['&' (rune pam %wtpm exps)]
::                    ['@' ;~(pfix pat (toad tkvt))]
::                    ['~' ;~(pfix sig (toad tksg))]
::                    ['!' (rune zap %wtzp expa)]
::                ==
::              ==
::            :-  '!'
::              ;~  pfix  zap
::                %-  stew
::                ^.  stet  ^.  limo
::                :~  [':' ;~(pfix col (toad expz))]
::                    ['.' ;~(pfix dot (toad |.(loaf(bug |))))]
::                    [',' (rune com %zpcm expb)]
::                    [';' (rune mic %zpmc expb)]
::                    ['>' (rune gar %zpgr expa)]
::                    ['<' (rune gal %zpgl exqc)]
::                    ['@' (rune pat %zppt expy)]
::                    ['=' (rune tis %zpts expa)]
::                    ['?' (rune wut %zpwt hinh)]
::                ==
::              ==
::        ==
::      --
::    --
--
