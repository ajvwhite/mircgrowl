;;;[ growl-notify.mrc ];;;;;;;;;;;;;;;;;;;
;; Author : Alexander White
;; Useage  : Read commented lines below
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Alias to get mIRCgrowl version info
alias mircgrowlver {
  var %mIRCgrowlVerInfo = $dll(mircgrowl.dll,version,null);
  //echo %mIRCgrowlVerInfo
}

;; this will let you know when your nickname is mentioned via the DLL
on *:TEXT:$(* $+ $me $+ *):#:{
  var %growlnot $1- $+ $chr(32) $+ :: $+ $chr(32) $+ said by $+ $chr(32) $+ $nick $+ $chr(32) $+ :: $+ $chr(32) $+ $chan $+ $chr(32) $+ - $+ $chr(32) $+ $network $+ $chr(32) $+ :: $+ $chr(32) $+ $time
  
  var %notifySucc = $dll(mircgrowl.dll,notifyChatMention,%growlnot);
  if ( %notifySucc != S_OK ) {
    ;; Add any error actions you may want if the notification isn't a success %notifySucc will have the error
  }
}

;; Deal with private messages
on *:TEXT:*:?:{
  var %growlprivnot $1- $+ $chr(32) $+ :: $+ $chr(32) $+ sent by $+ $chr(32) $+ $nick $+ $chr(32) $+ :: $+ $chr(32) $+ $network $+ $chr(32) $+ :: $+ $chr(32) $+ $time
  
  var %notifySucc = $dll(mircgrowl.dll,notifyPrivateMsg,%growlprivnot);
  if ( %notifySucc != S_OK ) {
    ;; Add any error actions you may want if the notification isn't a success %notifySucc will have the error
  }
}

;; Notify on file send complete
on *:FILESENT:*:{
  var %growlfilesent File Send Completed $+ $chr(9) $+ You have sent $+ $chr(32) $+ $filename $+ $chr(32) $+ to $+ $chr(32) $+ $nick $+ $chr(32) $+ :: $+ $chr(32) $+ $network $+ $chr(32) $+ :: $+ $chr(32) $+ $time
  
  var %notifySucc = $dll(mircgrowl.dll,notifyTransferStatus,%growlfilesent);
  if ( %notifySucc != S_OK ) {
    ;; Add any error actions you may want if the notification isn't a success %notifySucc will have the error
  }
}

;; Notify when a file is received
on *:FILERCVD:*:{
  var %growlfilerecieved File Received Completed $+ $chr(9) $+ You have received $+ $chr(32) $+ $filename $+ $chr(32) $+ from $+ $chr(32) $+ $nick $+ $chr(32) $+ :: $+ $chr(32) $+ $network $+ $chr(32) $+ :: $+ $chr(32) $+ $time
  
  var %notifySucc = $dll(mircgrowl.dll,notifyTransferStatus,%growlfilerecieved);
  if ( %notifySucc != S_OK ) {
    ;; Add any error actions you may want if the notification isn't a success %notifySucc will have the error
  }
}

;; Notify when a file send fails
on *:SENDFAIL:*:{
  var %growlfilesendfail File Sending Failed $+ $chr(9) $+ You have failed to send $+ $chr(32) $+ $filename $+ $chr(32) $+ to $+ $chr(32) $+ $nick $+ $chr(32) $+ :: $+ $chr(32) $+ $network $+ $chr(32) $+ :: $+ $chr(32) $+ $time
  
  var %notifySucc = $dll(mircgrowl.dll,notifyTransferStatus,%growlfilesendfail);
  if ( %notifySucc != S_OK ) {
    ;; Add any error actions you may want if the notification isn't a success %notifySucc will have the error
  }
}

;; Notify when a file recieve fails
on *:GETFAIL:*:{
  var %growlfilegetfail File Receive Failed $+ $chr(9) $+ You have failed to receive $+ $chr(32) $+ $filename $+ $chr(32) $+ from $+ $chr(32) $+ $nick $+ $chr(32) $+ :: $+ $chr(32) $+ $network $+ $chr(32) $+ :: $+ $chr(32) $+ $time
  
  var %notifySucc = $dll(mircgrowl.dll,notifyTransferStatus,%growlfilegetfail);
  if ( %notifySucc != S_OK ) {
    ;; Add any error actions you may want if the notification isn't a success %notifySucc will have the error
  }
}
