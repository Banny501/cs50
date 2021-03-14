
let lamp = new Lamp(0,0);
document.addEventListener('DOMContentLoaded',function() {
  document.querySelector('.lamp').addEventListener('click', function() {
    lamp.change(1,0);
    document.querySelector('.text_block').style.color = "white";
  })
})
