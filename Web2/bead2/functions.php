<?php

@session_start();
require_once('user.php');

function VALIDATE_ISBN($val){
    if(!filter_var($val,FILTER_VALIDATE_INT,array('options'=>array('min_range'=>0)))) return false;
    $num_length = strlen((string)$val);
    return ($num_length==10 || $num_length==13);
}

function save_to_file($file, $data) {
    file_put_contents($file, json_encode($data));
}

function load_from_file($file) {
    return json_decode(file_get_contents($file),true);
}

function get_book_count($input){
    $num=0;
    foreach ($input as $val){
        $curr = User::AddDataFile($val);
        $num+= $curr->book_count();
    }
    return $num;
}

function validate($input, $rules, &$data, &$result = null) {
    if($result == null) {
        $result = new Result();
    }
    
    $filtered_inputs = filter_var_array($input, $rules);

    foreach ($filtered_inputs as $key => $value) {
        $data[$key] = null;
        if (is_null($value) || is_empty($input, $key)) {
            if (isset($rules[$key]['default'])) {
                $data[$key] = $rules[$key]['default'];
            } else {
                $result->add_error("{$key} hiányzik");
            }
        } else if ($value === false) {
            $result->add_error($rules[$key]['errormsg']);
        } else {
            $data[$key] = $value;
        }
    }    
    return $result;
}

function allow($method) {
    if($_SERVER['REQUEST_METHOD'] != $method) {
        die('Bad Request!');    
    }
}

function is_empty($input, $key) {
    return !isset($input[$key]) || empty($input[$key]);
}

function redirect($url) {
    header("Location: ". $url);
    exit;
}

function save_to_flash($data) {
    $_SESSION['_flash'] = $data;
}

function load_from_flash() {
    if(isset($_SESSION['_flash'])) {
        $data = $_SESSION['_flash'];
        unset($_SESSION['_flash']);
        return $data;
    } else {
        return null;
    }
}

function login($user) {
    $_SESSION['logged_in'] = $user;
}

function logout() {
    unset($_SESSION['logged_in']);
}

function current_user() {
    return $_SESSION['logged_in'];
}

class Result {
    private $m_messages;
    private $m_warnings;
    private $m_errors;

    public function __construct($messages = [], $warnings = [], $errors = []) {
        $this->m_messages = $messages;
        $this->m_warnings = $warnings;
        $this->m_errors = $errors;
    }

    public function messages() {
        return $this->m_messages;
    }

    public function warnings() {
        return $this->m_warnings;
    }

    public function errors() {
        return $this->m_errors;
    }

    public function success() {
        return empty($this->m_errors);
    }

    public function add_message($message) {
        $this->m_messages[] = $message;
        return $this;
    }

    public function add_warning($warning) {
        $this->m_warnings[] = $warning;
        return $this;
    }

    public function add_error($error) {
        $this->m_errors[] = $error;
        return $this;
    }

    public function html() {
        foreach($this->m_errors as $error) {
            echo '<div class="alert alert-danger">'.$error.'</div>';
        }
        foreach($this->m_messages as $message) {
            echo '<div class="alert alert-info">'.$message.'</div>';
        }
        foreach($this->m_warnings as $warning) {
            echo '<div class="alert alert-warning">'.$warning.'</div>';
        }
    }
}

?>