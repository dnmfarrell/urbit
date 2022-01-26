/-  spider
/+  strandio
=,  strand=strand:spider
=,  card=card:agent:gall
^-  thread:spider
|=  arg=vase
=/  m  (strand ,vase)
^-  form:m
;<  ~  bind:m  (send-raw-card:strandio %pass /sub-priv %arvo %j %private-keys ~)
;<  res=[=wire =sign-arvo]  bind:m  take-sign-arvo:strandio
?>  ?=([%sub-priv ~] wire.res)
?>  ?=([%jael *] sign-arvo.res)
~&  +.sign-arvo.res
;<  ~  bind:m  (send-raw-card:strandio %pass /sub-priv %arvo %j %nuke ~)
(pure:m !>(~))
