$(document).ready(function(){
    var grid = $('.grid');
    var flagsLeft = $('#flags-left'),
    var result = $('#result');
    let width = 10;
    let bombAmount = 20;
    let flags = 0;
    let squares = [];
    let isGameOver = false;
  
    //create Board
    function createBoard() {
      flagsLeft.html(bombAmount);
      
      //get shuffled game array with random bombs
      var bombsArray = Array(bombAmount).fill('bomb');
      var emptyArray = Array(width*width - bombAmount).fill('empty');
      var gameArray = [].concat(bombsArray);
      var shuffledArray = gameArray.sort(() => Math.random() -0.5);
  
      for(let i = 0; i < width*width; i++) {
        var square = document.createElement('div')
        square.setAttribute('id', i)
        square.classList.add(shuffledArray[i])
        grid.appendChild(square)
        squares.push(square)
  
        //normal click
        square.addEventListener('click', function(e) {
          click(square)
        })
  
        //cntrl and left click
        square.oncontextmenu = function(e) {
          e.preventDefault()
          addFlag(square)
        }
      }
  
      //add numbers
      for (let i = 0; i < squares.length; i++) {
        let total = 0
        var isLeftEdge = (i % width === 0)
        var isRightEdge = (i % width === width -1)
  
        if (squares[i].classList.contains('valid')) {
          if (i > 0 && !isLeftEdge && squares[i -1].classList.contains('bomb')) total ++
          if (i > 9 && !isRightEdge && squares[i +1 -width].classList.contains('bomb')) total ++
          if (i > 10 && squares[i -width].classList.contains('bomb')) total ++
          if (i > 11 && !isLeftEdge && squares[i -1 -width].classList.contains('bomb')) total ++
          if (i < 98 && !isRightEdge && squares[i +1].classList.contains('bomb')) total ++
          if (i < 90 && !isLeftEdge && squares[i -1 +width].classList.contains('bomb')) total ++
          if (i < 88 && !isRightEdge && squares[i +1 +width].classList.contains('bomb')) total ++
          if (i < 89 && squares[i +width].classList.contains('bomb')) total ++
          squares[i].setAttribute('data', total)
        }
      }
    }
    createBoard()
  
    //add Flag with right click
    function addFlag(square) {
      if (isGameOver) return
      if (!square.classList.contains('checked') && (flags < bombAmount)) {
        if (!square.classList.contains('flag')) {
          square.classList.add('flag')
          square.innerHTML = ' 🚩'
          flags ++
          flagsLeft.innerHTML = bombAmount- flags
          checkForWin()
        } else {
          square.classList.remove('flag')
          square.innerHTML = ''
          flags --
          flagsLeft.innerHTML = bombAmount- flags
        }
      }
    }
  
    //click on square actions
    function click(square) {
      let currentId = square.id
      if (isGameOver) return
      if (square.classList.contains('checked') || square.classList.contains('flag')) return
      if (square.classList.contains('bomb')) {
        gameOver(square)
      } else {
        let total = square.getAttribute('data')
        if (total !=0) {
          square.classList.add('checked')
          if (total == 1) square.classList.add('one')
          if (total == 2) square.classList.add('two')
          if (total == 3) square.classList.add('three')
          if (total == 4) square.classList.add('four')
          square.innerHTML = total
          return
        }
        checkSquare(square, currentId)
      }
      square.classList.add('checked')
    }
  
  
    //check neighboring squares once square is clicked
    function checkSquare(square, currentId) {
      var isLeftEdge = (currentId % width === 0)
      var isRightEdge = (currentId % width === width -1)
  
      setTimeout(() => {
        if (currentId > 0 && !isLeftEdge) {
          var newId = squares[parseInt(currentId) -1].id
          var newSquare = document.getElementById(newId)
          click(newSquare)
        }
        if (currentId > 9 && !isRightEdge) {
          var newId = squares[parseInt(currentId) +1 -width].id
          var newSquare = document.getElementById(newId)
          click(newSquare)
        }
        if (currentId > 10) {
          var newId = squares[parseInt(currentId -width)].id
          var newSquare = document.getElementById(newId)
          click(newSquare)
        }
        if (currentId > 11 && !isLeftEdge) {
          var newId = squares[parseInt(currentId) -1 -width].id
          var newSquare = document.getElementById(newId)
          click(newSquare)
        }
        if (currentId < 98 && !isRightEdge) {
          var newId = squares[parseInt(currentId) +1].id
          var newSquare = document.getElementById(newId)
          click(newSquare)
        }
        if (currentId < 90 && !isLeftEdge) {
          var newId = squares[parseInt(currentId) -1 +width].id
          var newSquare = document.getElementById(newId)
          click(newSquare)
        }
        if (currentId < 88 && !isRightEdge) {
          var newId = squares[parseInt(currentId) +1 +width].id
          var newSquare = document.getElementById(newId)
          click(newSquare)
        }
        if (currentId < 89) {
          var newId = squares[parseInt(currentId) +width].id
          var newSquare = document.getElementById(newId)
          click(newSquare)
        }
      }, 10)
    }
  
    //game over
    function gameOver(square) {
      result.innerHTML = 'You lost the game!'
      isGameOver = true
  
      //show ALL the bombs
      squares.forEach(square => {
        if (square.classList.contains('bomb')) {
          square.innerHTML = '💣'
          square.classList.remove('bomb')
          square.classList.add('checked')
        }
      })
    }
  
    //check for win
    function checkForWin() {
      ///simplified win argument
    let matches = 0
  
      for (let i = 0; i < squares.length; i++) {
        if (squares[i].classList.contains('flag') && squares[i].classList.contains('bomb')) {
          matches ++
        }
        if (matches === bombAmount) {
          result.innerHTML = 'YOU WIN!'
          isGameOver = true
        }
      }
    }
  });