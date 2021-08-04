ps x | grep open5gs | tr -s ' ' ' ' | cut -d ' ' -f 2 | xargs kill
