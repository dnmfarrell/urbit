/-  *btc
|%
+$  credentials  [rpc-url=@t rpc-user=@t rpc-password=@t]
+$  status
  $%  [%host connected=? clients=(set ship)]
      [%client connected=? host=(unit ship)]
  ==
+$  action
  $%  [%check-status ~]
      [%get-block-count ~]
      [%balance =address]
      [%transactions =address]
  ==
::
+$  command
  $%  [%become-host =credentials]
      [%connect-as-client host=ship]
      [%allow-clients users=(set ship)]
  ==
--
