<?php require_once('functions.php');
require_once('user.php');
require_once('form.php');
require 'header.php';

?>
<html>
<head>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
</head>
<h1>BookWorms - Home</h1>
<h2>Üdv újra <?= current_user()['name'] ?> !</h2>

<h3>Jelenlegi könyvlistád:</h3>
    <div id="cocc">
        <!-- table will later be loaded inside here -->
    </div>
    <?php
    $page = !empty($_GET['page']) ? $_GET['page'] : 1;
    $users = load_from_file('data/users.json');
    $curruser = User::AddDataFile($users[current_user()['email']]);
    $list = $curruser->booklist();
    setcookie("listCookie", sizeof($list));
    ?>
    <table>
        <button id="PrevButton" type="submit" onclick="stepleft()" class="btn btn-default">Előző</button>
        <button id="NextButton" type="submit" onclick="stepright()" class="btn btn-default">Következő</button>
    </table>
<br>
<form action="addbookpage.php" method="post">
    <input type="hidden" name="page" value="" />
    <button type="submit" class="btn btn-default">Könyv hozzáadása</button>
</form>

<form action="logout.php" method="post">
    <button type="submit" class="btn btn-default">Kijelentkezés</button>
</form>

</html>

<script>

    let pageNumber = getURLParameter("page") != null ? getURLParameter("page") : 1;
    var listLength;

    $(document).ready(function () {
        $('#cocc').load('pagination.php?page=' + pageNumber)
        listLength = getCookieValue("listCookie") !== "" ? getCookieValue("listCookie") : 0;
        hideOrShowButtons(pageNumber);
	
	      $('body').delegate('.gomb', 'click', function(event) {
			    event.preventDefault();
			
			    var $this = $(this),
				    $id = $this.prop('id'),
				    $form = $this.closest('tr').find('form'),
				    $type = $this.find('input[name="type"]').length ? $this.find('input[name="type"]') : $('<input>').prop('type', 'hidden').prop('name', 'type');
			
			    $form.prepend($type.val($id));
			
			    $form.submit();
		    });
    });

    function changeurl(url){
        window.history.pushState("list","Title",url);
    }

    function stepleft() {
        pageNumber--;
        getTable();
    }

    function stepright() {
        pageNumber++;
        getTable();
    }

    function getTable(){
        changeurl('?page='+pageNumber);
        $('#cocc').load('pagination.php?page=' + pageNumber)
        hideOrShowButtons(pageNumber);
    }

    function hideOrShowButtons(pageNum) {
        if (pageNum == 1) {
            document.getElementById('PrevButton').style.display = 'none';
        } else {
            document.getElementById('PrevButton').style.display = 'block';
        }

        if (listLength <= pageNum*5) {
            document.getElementById('NextButton').style.display = 'none';
        } else {
            document.getElementById('NextButton').style.display = 'block';
        }

    }

    function getURLParameter(name) {
        return decodeURIComponent((new RegExp('[?|&]' + name + '=' + '([^&;]+?)(&|#|;|$)').exec(location.search) || [null, ''])[1].replace(/\+/g, '%20')) || null;
    }

    function getCookieValue(a) {
        var b = document.cookie.match('(^|;)\\s*' + a + '\\s*=\\s*([^;]+)');
        return b ? b.pop() : '';
    }
</script>