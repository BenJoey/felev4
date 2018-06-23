<?php require_once('functions.php');
require_once('user.php');
require_once('form.php');
$users = load_from_file('data/users.json');
$curruser = User::AddDataFile($users[current_user()['email']]);
$list = $curruser->booklist();

$page = !empty($_GET['page']) ? $_GET['page'] : 1;

ksort($list);
$list2 = array_slice($list, ((int)$page - 1) * 5, 5, true);

list_the_list($list2, $page);

function list_the_list($list2, $page) {
    echo "<table><tr><th>Szerző</th><th>Cím</th><th>Oldalszám</th>
        <th>Kategória</th><th>ISBN</th><th>Elolvasva?</th><th>Módosítás</th>
        <th>Törlés</th></tr>";
    foreach ($list2 as $val) {
        $book = new Book($val);
        echo "<tr>" . $book->getTableRaw();?>
            <th><button id="mod" type="button" class="gomb">Módosítás</button></th>
            <th><button id="del" type="button" class="gomb">Törlés</button></th>
	          <th>
		          <form action="modify.php" method="POST" class="modify-book">
			          <input type="hidden" name="isbn" value="<?=$book->getISBN()?>" />
			          <input type="hidden" name="page" value="<?=$page?>" />
		          </form>
	          </th>
        <?php
        echo "</tr>";
    }
    echo "</table>";
}

?>