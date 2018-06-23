<?php

require_once('functions.php');
require_once('user.php');
require_once('form.php');

allow('POST');

$users = load_from_file('data/users.json');
$curruser = User::AddDataFile($users[current_user()['email']]);
if(load_from_flash()=="mod")$mod=true;
else{$mod=false;}
$result = new Result();
$data = [];

$rules = [
    BookForm::BookAuthor => [
        'filter' => FILTER_DEFAULT,
        'errormsg' => 'A megadott szerző nem megfelelő (szöveg) formátumú!'
    ],
    BookForm::BookTitle => [
        'filter' => FILTER_DEFAULT,
        'errormsg' => 'A megadott cím nem megfelelő (szöveg) formátumú!'
    ],
    BookForm::BookPages => [
        'filter' => FILTER_VALIDATE_INT,
        'errormsg' => 'A megadott oldalszám nem megfelelő (szám) formátumú!'
    ],
    BookForm::BookCategory => [
        'filter' => FILTER_DEFAULT,
        'errormsg' => 'A megadott kategória nem megfelelő (szöveg) formátumú!'
    ],
    BookForm::BookISBN => [
        'filter' => FILTER_VALIDATE_ISBN,
        'errormsg' => 'A megadott ISBN nem megfelelő (szám) formátumú!'
    ]
];

validate($_POST, $rules, $data, $result);

// if(isset($_POST['read'])){
//     $data['read']=1;
// }else{
//     $data['read']=0;
// }
$data['read'] = isset($_POST['read']) ? 1 : 0;

if(!VALIDATE_ISBN($data[BookForm::BookISBN])){
    $result->add_error("Az ISBN szám nem megfelelő hosszú.");
}

if($data['page_num']<=0){
    $result->add_error("Az oldalszám nem lehet negatív vagy 0");
}

if(!$result->success()) {
    if($mod){
        $toflash=[
            'res' => $result,
            'bookdata' => $data
        ];
    }else{
        $toflash=$result;
    }
    save_to_flash($toflash);
    redirect('addbookpage.php');
    die();
}

$isbn=$data[BookForm::BookISBN];

if($mod){
    $curruser->deleteBook($isbn);
}

if(!$curruser->benvanemar($isbn)){
    $book = new Book($data);
    $curruser->AddBook($book);
    $users[$curruser->mail()] = $curruser;
} else {
    $result->add_error("Ez a könyv már szerepel az adatbázisban.");
}

save_to_flash($result);

if($result->success()) {
    save_to_file("data/users.json", $users);
    redirect('list.php');
} else {
    redirect('addbookpage.php');
}

?>