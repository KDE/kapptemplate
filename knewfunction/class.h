if [ ! -f $HDR_FILE ];
then
	$ECHO "$HDR_FILE does not exist!  Aborting.";
	exit 1;
fi
$ECHO "Creating '$RETURN_VAL $FUNCTION_NAME($PARAMS)' in $HDR_FILE...";

if [ -f "$HDR_FILE.tmp" ];
then
	rm -f "$HDR_FILE.tmp" >& /dev/null;
	touch "$HDR_FILE.tmp"
fi

IFS=" \n";
unset IN_CLASS;
unset IN_TYPE;
cat $HDR_FILE | while read LINE
do
	if [ "$IN_CLASS" ];
	then
		if [ "`$ECHO $LINE | sed 's@^\(};\).*@\1@'`" = "};" ];
		then
			$ECHO "$FUNCTION_TYPE:" >> $HDR_FILE.tmp;
			unset IN_CLASS;
			$ECHO "\t/**" >> $HDR_FILE.tmp;
			$ECHO "\t * The description for this function goes here" >> $HDR_FILE.tmp;
			$ECHO "\t */" >> $HDR_FILE.tmp;
			$ECHO "\t$FUNCTION_PROTO;" >> $HDR_FILE.tmp;
		elif [ "`$ECHO $LINE | sed 's@[ \t]*\([a-zA-Z ]*\):.*@\1@'`" = "$FUNCTION_TYPE" ];
		then
			IN_TYPE=1;
		elif [ "$IN_TYPE" ];
		then
			unset IN_CLASS;
			$ECHO "\t/**" >> $HDR_FILE.tmp;
			$ECHO "\t * The description for this function goes here" >> $HDR_FILE.tmp;
			$ECHO "\t */" >> $HDR_FILE.tmp;
			$ECHO "\t$FUNCTION_PROTO;" >> $HDR_FILE.tmp;
		fi
	elif [ "`$ECHO $LINE | sed 's@^class \([a-zA-Z]*\)[^;]*@\1@'`" = "$CLASS_NAME" ];
	then
		IN_CLASS=1;
	fi
	$ECHO "$LINE" >> $HDR_FILE.tmp;
done

rm -f "$HDR_FILE";
mv "$HDR_FILE.tmp" "$HDR_FILE";
