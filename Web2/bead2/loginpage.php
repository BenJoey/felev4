<?php require_once('functions.php'); require_once('form.php');require('header.php'); ?>
<h1>BookWorms - Bejelentkezés</h1>

<?php $result = load_from_flash(); if($result !== null && ($result instanceof Result)) $result->html(); ?>

<form action="login.php" method="post">
    <div class="form-group">
        <label for="email" class="control-label">E-mail cím</label><br />
        <input name="<?= LogInForm::LoginEmail ?>" id="email" type="text" placeholder="example@host.com" class="form-control"><br />
    </div>
    <div class="form-group">
        <label for="passwd2" class="control-label">Jelszó</label><br />
        <input name="<?= LogInForm::LoginPassword  ?>" id="passwd" type="password" class="form-control"><br />
    </div>
    <input type="submit" value="Bejelentkezés" class="btn btn-primary">
</form>