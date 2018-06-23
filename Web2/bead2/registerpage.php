<?php require_once('functions.php'); require_once('form.php');require 'header.php'; ?>
<h1>BookWorms - Regisztráció</h1>

<?php $result = load_from_flash(); if($result !== null && ($result instanceof Result)) $result->html(); ?>

<form action="register.php" method="post">
    <div class="form-group">
        <label for="username" class="control-label">Teljes név</label><br />
        <input name="<?= RegForm::RegisterName ?>" id="username" type="text" class="form-control"><br />
    </div>
    <div class="form-group">
        <label for="email" class="control-label">E-mail cím</label><br />
        <input name="<?= RegForm::RegisterEmail ?>" id="email" type="text" placeholder="example@host.com" class="form-control"><br />
    </div>
    <div class="form-group">
        <label for="passwd2" class="control-label">Jelszó</label><br />
        <input name="<?= RegForm::RegisterPassword  ?>" id="passwd" type="password" class="form-control"><br />
    </div>
    <div class="form-group">
        <label for="passwd" class="control-label">Jelszó újra</label><br />
        <input name="<?= RegForm::RegisterPasswordRe  ?>" id="passwd2" type="password" class="form-control"><br />
    </div>
    <input type="submit" value="Regisztráció" class="btn btn-primary">
</form>