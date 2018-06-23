<?php
require_once('functions.php');
require_once('addbookpage.php');
allow('POST');

$users = load_from_file('data/users.json');
$curruser = User::AddDataFile($users[current_user()['email']]);

if($_POST['type']=="del"){
    $curruser->deleteBook($_POST['isbn']);
    $users[$curruser->mail()] = $curruser;
    save_to_file("data/users.json", $users);
    redirect('list.php?page='.(!empty($_POST['page']) ? $_POST['page'] : 1));
} elseif($_POST['type']=="mod") {
    save_to_flash($curruser->booklist()[$_POST['isbn']]);
    redirect('addbookpage.php');
}
?>