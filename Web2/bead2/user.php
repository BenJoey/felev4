<?php

class User implements JsonSerializable {
    private $u_name;
    private $u_email;
    private $u_pwhash;
    private $u_books;
    
    private function __construct($name, $email, $pwhash, $books=[]) {
        $this->u_name = $name;
        $this->u_email = $email;
        $this->u_pwhash = $pwhash;
        $this->u_books = $books;
    }

    public static function AddDataManual($name, $email, $password){
        return new User($name, $email, password_hash($password, PASSWORD_DEFAULT));
    }

    public static function AddDataFile($data) {
        return new User($data['name'], $data['email'], $data['pwhash'], $data['books']);
    }

    public function mail() {
        return $this->u_email;
    }

    public function pw_check($password) {
        return password_verify($password, $this->u_pwhash);
    }

    public function AddBook($newbook){
        $this->u_books[$newbook->getISBN()]=$newbook->jsonSerialize();
    }

    public function booklist(){
        return $this->u_books;
    }

    public function benvanemar($isbn){
        return isset($this->u_books[$isbn]);
    }

    public function book_count(){
        return count($this->u_books);
    }

    public function deleteBook($isbn){
        unset($this->u_books[$isbn]);
    }

    public function jsonSerialize() {
        return [
            'name' => $this->u_name,
            'email' => $this->u_email,
            'pwhash' => $this->u_pwhash,
            'books' => $this->u_books
        ];
    }
}

class Book implements JsonSerializable {
    private $author;
    private $title;
    private $page_num;
    private $category;
    private $ISBN;
    private $read;

    public function __construct($data) {
        $this->author = $data[BookForm::BookAuthor];
        $this->title = $data[BookForm::BookTitle];
        $this->page_num = $data[BookForm::BookPages];
        $this->category = $data[BookForm::BookCategory];
        $this->ISBN = $data[BookForm::BookISBN];
        $this->read = $data[BookForm::BookRead];
    }

    public function getISBN(){
        return $this->ISBN;
    }

    public function getTableRaw(){
        $val = "<th>".$this->author."</th>"."<th>".$this->title."</th>"."<th>".$this->page_num."</th>"."<th>".$this->category."</th>"."<th>".$this->ISBN."</th>";
        if($this->read){
            $val = $val."<th>Igen</th>";
        }else{
            $val = $val."<th>Nem</th>";
        }
        return $val;
    }

    public function jsonSerialize() {
        return [
            'author' => $this->author,
            'title' => $this->title,
            'page_num' => $this->page_num,
            'category' => $this->category,
            'ISBN' => $this->ISBN,
            'read' => $this->read
        ];
    }
}

?>