CREATE DEFINER=`typetwo`@`%` PROCEDURE `admin_delete`(
	IN in_username VARCHAR(16)
)
BEGIN
	DECLARE v_userid INT;
    DECLARE user_not_found CONDITION FOR SQLSTATE 'HY000';

	SET v_userid = 0;
    SELECT user_id INTO v_userid 
    FROM user, admin
    WHERE username = in_username
    AND user_id = fk_admin_userid_user;
    
    DELETE FROM admin WHERE fk_admin_userid_user = v_userid;
END

CREATE DEFINER=`typetwo`@`%` PROCEDURE `admin_delete`(
	IN in_username VARCHAR(16)
)
BEGIN
	DECLARE v_userid INT;
    DECLARE user_not_found CONDITION FOR SQLSTATE 'HY000';

	SET v_userid = 0;
    SELECT user_id INTO v_userid 
    FROM user, admin
    WHERE username = in_username
    AND user_id = fk_admin_userid_user;
    
    DELETE FROM admin WHERE fk_admin_userid_user = v_userid;
END

CREATE DEFINER=`typetwo`@`%` PROCEDURE `admin_delete`(
	IN in_username VARCHAR(16)
)
BEGIN
	DECLARE v_userid INT;
    DECLARE user_not_found CONDITION FOR SQLSTATE 'HY000';

	SET v_userid = 0;
    SELECT user_id INTO v_userid 
    FROM user, admin
    WHERE username = in_username
    AND user_id = fk_admin_userid_user;
    
    DELETE FROM admin WHERE fk_admin_userid_user = v_userid;
END

CREATE DEFINER=`typetwo`@`%` PROCEDURE `admin_delete`(
	IN in_username VARCHAR(16)
)
BEGIN
	DECLARE v_userid INT;
    DECLARE user_not_found CONDITION FOR SQLSTATE 'HY000';

	SET v_userid = 0;
    SELECT user_id INTO v_userid 
    FROM user, admin
    WHERE username = in_username
    AND user_id = fk_admin_userid_user;
    
    DELETE FROM admin WHERE fk_admin_userid_user = v_userid;
END