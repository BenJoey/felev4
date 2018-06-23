<?php

require_once('functions.php');
require_once('user.php');
require_once('form.php');

allow('POST');

$users = load_from_file('data/users.json');
$result = new Result();
$data = [];

$rules = [
    RegForm::RegisterName => [
        'filter' => FILTER_DEFAULT,
        'errormsg' => 'A megadott felhasználónév nem megfelelő (szöveg) formátumú!'
    ],
    RegForm::RegisterEmail => [
        'filter' => FILTER_VALIDATE_EMAIL,
        'errormsg' => 'A megadott email-cím nem megfelelő formátumú!'
    ],
    RegForm::RegisterPassword => [
        'filter' => FILTER_DEFAULT,
        'errormsg' => 'A megadott jelszó nem megfelelő (szöveg) formátumú!'
    ],
    RegForm::RegisterPasswordRe => [
        'filter' => FILTER_DEFAULT,
        'errormsg' => 'Az ismételt jelszó nem megfelelő (szöveg) formátumú!'
    ]
];

validate($_POST, $rules, $data, $result);

if(!$result->success()) {
    save_to_flash($result);
    redirect('registerpage.php');
    die();
}

$name = $data[RegForm::RegisterName];
$email = $data[RegForm::RegisterEmail];
$pw1 = $data[RegForm::RegisterPassword];
$pw2 = $data[RegForm::RegisterPasswordRe];

if(!isset($users[$email])) {
    if($pw1 == $pw2) {
        $user = User::AddDataManual($name, $email, $pw1);
        $users[$email] = $user;
    } else {
        $result->add_error("A két jelszó nem egyezik!");
    }
} else {
    $result->add_error("Ez az email-cím már foglalt!");
}

save_to_flash($result);

if($result->success()) {
    save_to_file("data/users.json", $users);
    login($user->jsonSerialize());
    redirect('list.php');
} else {
    redirect('registerpage.php');
}

?>