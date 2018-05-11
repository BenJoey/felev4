var prevclickedPic, isRevealed, Player1Score, Player2Score, currentPlayername;
var currentPlayer, gameMode, canPlay, player1name, player2name;

canvas.addEventListener("click", function(e){
    if(canPlay){
        let rect = canvas.getBoundingClientRect();
        let x = Math.floor((e.clientX - rect.left)/cellSize),
        y = Math.floor((e.clientY - rect.top)/cellSize);
        clicked(x,y);
    }
}, true);

function gameInit(mode){
    currentPlayer = 0; gameMode = mode; canPlay = true;
    switch(gameMode){
        case 0:player1name = "Játékos";player2name = "";break;
        case 1:player1name = "Játékos";player2name = "Gép";break;
        case 2:player1name = "1. Játékos";player2name = "2. Játékos";break;
    }
    Player1Score = 0; Player2Score = 0; isRevealed = false;
    currentPlayername = player1name;
}

function clicked(i,j){
    let temp = findimagekoord(i,j);
    if(!images[temp].revealed && !images[temp].found){
        images[temp].revealed = true;
        if(!isRevealed){
            prevclickedPic = temp;
            isRevealed = true;
            drawTable();
        }
        else{
            canPlay = false;
            drawTable();
            setTimeout(compareimages(temp, prevclickedPic), 2000);
            isRevealed = false;
        }
    }
}

function compareimages(egyik, masik){
    return function(){
        if(images[egyik].OrdNum == images[masik].OrdNum){
            images[egyik].found = true;
            images[masik].found = true;
            if(gameMode != 0){
                switch(currentPlayer){
                    case 0:Player1Score++;break;
                    case 1:Player2Score++;break;
                }
            }
        }
        if(gameMode == 0)Player1Score++;
        images[egyik].revealed = false;
        images[masik].revealed = false;
        drawTable();
        nextPlayer();
        switch(currentPlayer){
            case 0:currentPlayername = player1name;break;
            case 1:currentPlayername = player2name;break;
        }
        updateMSG();
        if(end)GameOver();
    }
}

function updateMSG(){
    let temp;
    if(gameMode == 0){
        temp = player1name + " lépései: " + Player1Score;
    }
    else{
        temp = "Jelenleg játszik: " + currentPlayername + "<br/>";
        temp += player1name + " pontjai: " + Player1Score + "<br/>";
        temp += player2name + " pontjai: " + Player2Score;
    }
    $("#gametext").innerHTML = temp;
}

function findimagekoord(x,y){
    for(let i = 0; i < images.length;++i){
        if(images[i].x == x && images[i].y == y){
            return i;
        }
    }
}

function aistep(){
    let x = Math.floor(Math.random() * gameSize),
    y = Math.floor(Math.random() * gameSize),
    temp = images[findimagekoord(x,y)];
    while(temp.revealed || temp.found){
        x = Math.floor(Math.random() * gameSize);
        y = Math.floor(Math.random() * gameSize);
        temp = images[findimagekoord(x,y)];
    }
    clicked(x,y);
}

function aiturn(){
    setTimeout(aistep, 1000);
    setTimeout(aistep, 3000);
}

function nextPlayer(){
    if(gameMode == 1 && currentPlayer == 0 && !end){
        currentPlayer = 1;
        aiturn();
    }
    else {
        if(gameMode != 0)currentPlayer = (currentPlayer + 1) % 2;
        canPlay = true;
    }
}