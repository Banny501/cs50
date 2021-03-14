

    var ansver = "1111";
    var res = Math.floor(Math.random() * 14 + 1).toString(2).padStart(4,0)

    let lamps = [];
    for (var i = 0; i < res.length; i++)
    {
      lamps[i] = new Lamp(res.charAt(i), i);
    }


    document.addEventListener('DOMContentLoaded',function() {
          let lamp = document.querySelectorAll('.lamp');
          for (let i = 0; i < lamp.length; i++) {
              lamp[i].addEventListener('click', function() {
                  switch (i) {
                    case 0:
                      lamps[0].invert(0);
                      lamps[2].invert(2);
                      break;
                    case 1:
                      lamps[1].invert(1);
                      break;
                    case 2:
                      lamps[1].invert(1);
                      lamps[2].invert(2);
                      break;
                    case 3:
                      lamps[1].invert(1);
                      lamps[2].invert(2);
                      lamps[3].invert(3);
                      break;
                  }
            })
          }
          let check = document.querySelector('.butt');
          check.addEventListener('click',function() {
              res = "";
            for (var i = 0; i < lamps.length; i++) {
              res += lamps[i].value;
            }
            if (res == ansver) {
              document.getElementById("answer").innerHTML = "Well done";
              document.getElementById("next").innerHTML = "Next";
            }
            else {
              document.getElementById("answer").innerHTML = "I don't think so";
            }
          })
      });
