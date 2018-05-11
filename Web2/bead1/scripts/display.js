function $(selector) {
    return document.querySelector(selector);
}

function delegate(parent, children, type, handler) {
    function delegatedFunction(event) {
      let target = event.target;
      if (target.matches(`${parent} ${children}, ${parent} ${children} *`)) {
        while (!target.matches(children)) {
          target = target.parentNode;
        }
        return handler.call(target, event);
      }
    }
    $(parent).addEventListener(type, delegatedFunction);
  }
var devwidth = (window.innerWidth > 0) ? window.innerWidth : screen.width;
var devheight = document.documentElement.clientHeight * 0.60;  
var gameSize, diff, images, tomb, end, cellSize;
var canvas = $("#gameTable"); 
var ctx = canvas.getContext("2d");
var title = $("#gameTitle");
delegate('body', '.gomb', 'click', setGame);
delegate('body', '.home_button', 'click', gamestart);

function setCellSize(){
    let temp = (devwidth > devheight ? devheight : devwidth)/gameSize;
    cellSize = temp < 100 ? temp : 100;
}

function setGame(){
    let gm;
    gameSize = parseInt($("#tablesize").options[$("#tablesize").selectedIndex].value);
    diff = $("#difficulty").options[$("#difficulty").selectedIndex].value;
    let temp = $("#gamemode").options[$("#gamemode").selectedIndex].value;
    switch(temp){
        case "solo": gm = 0;break;
        case "ai":gm = 1;break;
        case "twoplayer":gm = 2;break;
    }
    setCellSize();
    gameInit(gm);
    $("#menu").style.display = "none";
    $("#game").style.display = "block";
    init();
}

function gamestart(){
    $("#menu").style.display = "block";
    $("#game").style.display = "none";
    $("#end").style.display = "none";
}

function init(){
    images = []; tomb = []; end = false;
    createCanvas();
    title.innerHTML = "Kiválasztott játékmód:<br/>";

    switch(gameMode){
        case 0:title.innerHTML += "Solo játék, ";break;
        case 1:title.innerHTML += "Gép elleni játék, ";break;
        case 2:title.innerHTML += "Kétjátékos mód, ";break;
    }

    title.innerHTML += gameSize + "x" + gameSize + "-es pályán, ";

    let temp = "";
    switch(diff){
        case "easy": temp = "könnyű";break;
        case "medium": temp = "közepesen nehéz";break;
        case "hard": temp = "nehéz";
    }

    title.innerHTML += temp + " képekkel";

    for(let i = 0; i < (gameSize*gameSize/2);++i){
        tomb.push(i+1);
        tomb.push(i+1);
    }
    shuffle(tomb);
    createImagesTable()
    drawTable(); updateMSG();
}

function shuffle(a) {
    var j, x, i;
    for (i = a.length - 1; i > 0; i--) {
        j = Math.floor(Math.random() * (i + 1));
        x = a[i];
        a[i] = a[j];
        a[j] = x;
    }
}

function createCanvas(){
    canvas.width = gameSize*cellSize;
    canvas.height = gameSize*cellSize;
    for(let i = 0; i < gameSize; ++i) {
        for(let j = 0; j < gameSize; ++j) {
            ctx.strokeStlye = "#000";
            ctx.strokeRect(i * cellSize, j * cellSize, cellSize, cellSize);
        }
    }
}

function createImagesTable(){
    for(let i = 0; i < gameSize; ++i){
        for(let j = 0; j < gameSize; ++j){
            picNum = tomb[i*gameSize+j];
            add_image(picNum,i,j);
        }
    }
}

function drawTable(){
    end = true; //ha minden képnek megvan a párja a játéknak vége
    for(let i = 0; i < images.length;++i){
        draw(images[i]);
        end = end && images[i].found;
    }
}

function add_image(Order, koordX, koordY){
    images.push({
        x: koordX,
        y: koordY,
        OrdNum: Order,
        revealed: false,
        found: false,
        source: "images/"+diff+"/"+Order+".png"
    });
}

function draw(tile){
    let imgObj = new Image();
    imgObj.onload = function() {
        ctx.save();
        ctx.drawImage(imgObj, tile.x*cellSize, tile.y*cellSize, cellSize, cellSize);
        ctx.restore();
    }
    if(tile.found) imgObj.src = "images/kuuhaku.png";
    else if(tile.revealed) imgObj.src = tile.source; 
    else{imgObj.src = "images/back.png";}
}

function GameOver(){
    $("#game").style.display = "none";
    $("#end").style.display = "block";
    let text = "";
    if(gameMode == 0){
        text = "<h3>A játékot " + Player1Score + " lépésből oldottad meg.</h3>";
    }
    else{
        if(Player1Score == Player2Score){
            text = "<h3>A játék döntetlen lett.</h3>";
            text += "Mindkét játékos " + Player1Score + " pontot ért el."
        }
        else{
            winner = Player1Score > Player2Score ? player1name : player2name;
            text = "<h3>A " + winner + " nyert.</h3>";
            text += player1name + " pontjai: "+Player1Score+"<br/>";
            text += player2name + " pontjai: "+Player2Score;
        }
    }
    $("#endgame").innerHTML = text;
}