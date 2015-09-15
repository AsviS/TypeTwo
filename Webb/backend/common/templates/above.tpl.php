<?php if($userSession->isLoggedIn()): ?>
	<a id='above-logout' href='/typetwo/user/logout'>Logout</a>
	<p><?=$_SESSION['user']?></p>
<?php else: ?>
	<a id='above-login' href='/typetwo/user/login'>Login</a>
<?php endif; ?>