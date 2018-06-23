<?php

require_once('functions.php');
$users = load_from_file('data/users.json');

require 'header.php';
if(isset($_SESSION['logged_in'])){
    redirect('list.php');
}
?>

<h1>BookWorms - Főoldal</h1>
<div>
    <h2>Mi ez az oldal?</h2>
    <p>Az oldal célja, hogy a felhasználók könnyen és átláthatóan tudják rendezni és számontartani az elolvasott(vagy éppen olvasott) könyveiket.</p>
    <h2>Hogyan tudom használni?</h2>
    <p>Egyszerű emailes regisztráció után teljesen ingyenesen igénybe veheted az oldalt.</p><br>
    <p>Jelenleg <?= count($users)?> felhasználó <?= get_book_count($users)?> darab könyve szerepel az adatbázisunkban.</p><br>
    <p>Ha már tag vagy, akkor <a href="loginpage.php">ide kattintva</a> tudsz bejelentkezni, ha még nem akkor pedig <a href="registerpage.php">kattints ide</a>, hogy regisztrálj.</p>
</div>