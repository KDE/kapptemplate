if [ -f $HDR_FILE ];
then
	$ECHO "$HDR_FILE already exists!  Aborting.";
	exit 1;
fi
echo "Creating $CLASS_NAME in $HDR_FILE...";

if [ "$PARENT" ];
then
	PARENT_HDR="#include <$PARENT_LC.h>";
	PARENT_DECL=": public $PARENT";
	# ugly hack to check for things like QWidget
	if [ "`$ECHO $PARENT | sed 's@^\(.\).*@\1@'`"  = "Q" ];
	then
		PARENT_PARAM="QWidget *parent = 0";
	fi
fi

cat << EOF > $HDR_FILE
#ifndef ${CLASS_NAME_UC}_H
#define ${CLASS_NAME_UC}_H
$PARENT_HDR

/**
 * The long description for this class goes here
 *
 * @version This is the short description
 * @author $AUTHOR <$EMAIL>
 * @version 0.1
 */
class $CLASS_NAME $PARENT_DECL
{
public:
	/**
	 * Default Constructor
	 */
	$CLASS_NAME($PARENT_PARAM);

	/**
	 * Copy Constructor
	 */
	$CLASS_NAME(const $CLASS_NAME&);

	/**
	 * Destructor
	 */
	virtual ~$CLASS_NAME();

protected:
};
#endif // ${CLASS_NAME_UC}_H
