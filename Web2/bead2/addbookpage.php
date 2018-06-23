<?php 

require_once('functions.php');
require_once('form.php');
require_once('user.php');
require 'header.php';
$auth="";$title="";$pages="";$cat="";$ro="";$isbn="";$isread="";$func="Hozzáadás";
$fromflash=load_from_flash();
if(!($fromflash instanceof Result) && isset($fromflash['bookdata']))$val=$fromflash['bookdata'];
else{
    $val=$fromflash;
}
if($val!==null && !($val instanceof Result) && isset($val['author'])){
    $auth=$val['author'];
    $title=$val['title'];
    $pages=$val['page_num'];
    $cat=$val['category'];
    $isbn=$val['ISBN'];
    if($val['read']){$isread="checked";}
    $func="Módosítás";
    $ro="readonly";
    if(isset($fromflash['res']))$val=$fromflash['res'];
    save_to_flash("mod");
}

?>
<h1>BookWorms - Könyv <?=$func?></h1>
<?php if($val !== null && ($val instanceof Result)) $val->html(); echo "<br />"; ?>

<form action="addbook.php" method="post">
    <div class="form-group">
        <label class="control-label">Könyv szerzője</label><br />
        <input name="<?= BookForm::BookAuthor ?>" type="text" class="form-control" value="<?=$auth?>"><br />
    </div>
    <div class="form-group">
        <label class="control-label">Könyv címe</label><br />
        <input name="<?= BookForm::BookTitle ?>" type="text" class="form-control" value="<?=$title?>"><br />
    </div>
    <div class="form-group">
        <label class="control-label">Oldalak száma</label><br />
        <input name="<?= BookForm::BookPages ?>" type="number" class="form-control" value="<?=$pages?>"><br />
    </div>
    <div class="form-group">
        <label class="control-label">Kategória</label><br />
        <input list="categs" name="<?= BookForm::BookCategory ?>" value="<?=$cat?>">
        <datalist id="categs">
            <option value="Krimi">
            <option value="Sci-fi">
            <option value="Fantasy">
            <option value="Romantika">
            <option value="Vígjáték">
            <option value="Mese">
            <option value="Ismeret terjesztő">
            <option value="Életrajz">
            <option value="Gasztronómia">
            <option value="Horror">
        </datalist>
    </div>
    <div class="form-group">
        <label class="control-label">A könyv ISBN száma</label><br />
        <input name="<?= BookForm::BookISBN ?>" type="number" class="form-control" value="<?=$isbn?>" <?=$ro?>><br />
    </div>
    <div class="form-group">
        <label class="control-label">Elolvastad már?</label>
        <input name="<?= BookForm::BookRead ?>" type="checkbox" class="form-control" <?=$isread?>><br />
    </div>
    <br /><input type="submit" value="<?=$func?>" class="btn btn-primary">
</form>