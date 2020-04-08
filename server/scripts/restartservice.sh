echo "a">>/tmp/config.aux 				#Stop the server
echo >/tmp/config.aux 					#Clean
systemctl restart SHserver				#Restart the service
