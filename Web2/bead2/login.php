<?php

require_once('functions.php');
require_once('user.php');
require_once('form.php');

allow('POST');

$users = load_from_file('data/users.json');
$result = new Result();
$data = [];

$rules = [
    LogInForm::LoginEmail => [
        'filter' => FILTER_VALIDATE_EMAIL,
        'errormsg' => 'A megadott email-cím nem megfelelő formátumú!'
    ],
    LogInForm::LoginPassword => [
        'filter' => FILTER_DEFAULT,
        'errormsg' => 'A megadott jelszó nem megfelelő (szöveg) formátumú!'
    ]
];

validate($_POST, $rules, $data, $result);

if(!$result->success()) {
    save_to_flash($result);
    redirect('loginpage.php');
    die();
}

$email = $data[LogInForm::LoginEmail];
$pw1 = $data[LogInForm::LoginPassword];

if(isset($users[$email])) {
    $user = User::AddDataFile($users[$email]);
    if($user->pw_check($pw1)) {
        login($user->jsonSerialize());
    } else {
        $result->add_error("Hibás email-cím vagy jelszó!");
    }
} else {
    $result->add_error("Hibás email-cím vagy jelszó!");
}

save_to_flash($result);

if($result->success()) {
    redirect('list.php');
} else {
    redirect('loginpage.php');
}

?>