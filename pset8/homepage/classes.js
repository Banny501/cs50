
    const light_file = "images/lamp_light.jpg"
    const dark_file = "images/lamp_dark.jpg"

    class Lamp
    {
      constructor(val, num)
      {
        if (val == 1)
        {
          this.image = light_file;
          this.value = '1';
          document.getElementById('lamp'+num).src = light_file;
        }
        else if (val == 0)
        {
          this.image = dark_file;
          this.value = '0';
          document.getElementById('lamp'+num).src = dark_file;
        }
      }

      change (val, num)
      {
        if (val == 1)
        {
          this.image = light_file;
          this.value = '1';
          document.getElementById('lamp'+num).src = light_file;
        }
        else if (val == 0)
        {
          this.image = dark_file;
          this.value = '0';
          document.getElementById('lamp'+num).src = dark_file;
        }
      }

      invert (num)
      {
        if (this.image == light_file)
        {
          this.image = dark_file;
          this.value = '0';
          document.getElementById('lamp'+num).src = dark_file;
        }
        else if (this.image == dark_file)
        {
          this.image = light_file;
          this.value = '1';
          document.getElementById('lamp'+num).src = light_file;
        }
      }
    }
