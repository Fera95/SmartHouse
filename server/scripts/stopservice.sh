echo "a">>/tmp/config.aux 				#Stop the daemon
systemctl stop SHserver					#Stop the service	
echo >/tmp/config.aux 					#Clean
