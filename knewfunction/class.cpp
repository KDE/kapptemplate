if [ ! -f $CPP_FILE ];
then
	$ECHO "$CPP_FILE does not exist!  Aborting.";
	exit 1;
fi
echo "Creating '$RETURN_VAL $CLASS_NAME::$FUNCTION_NAME($PARAMS)' in $CPP_FILE...";

cat << EOF >> $CPP_FILE

$RETURN_VAL $CLASS_NAME::$FUNCTION_NAME($PARAMS)
{
}
