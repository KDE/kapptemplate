if [ -f $CPP_FILE ];
then
	$ECHO "$CPP_FILE already exists!  Aborting.";
	exit 1;
fi
echo "Creating $CLASS_NAME in $CPP_FILE...";

if [ "$PARENT" ];
then
	PARENT_DECL=": $PARENT(parent)";
	# ugly hack to check for things like QWidget
	if [ "`$ECHO $PARENT | sed 's@^\(.\).*@\1@'`"  = "Q" ];
	then
		PARENT_PARAM="QWidget *parent";
	fi
fi

cat << EOF > $CPP_FILE
#include <$HDR_FILE>

$CLASS_NAME::$CLASS_NAME($PARENT_PARAM) $PARENT_DECL
{
}

$CLASS_NAME::$CLASS_NAME(const $CLASS_NAME& copy)
{
	*this = copy;
}

$CLASS_NAME::~$CLASS_NAME()
{
}
