const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

  <head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width initial-scale=1'>
    <title> Black Box 2.0 Counter</title>
    <!-- <link rel="stylesheet" href="https://use.typekit.net/sts2yah.css"> -->
    <style>
    body{
        background-position: center; 
        background-repeat: no-repeat; 
        background-size: cover; 
        background-color:  rgb(0, 0, 0);
        font-family: politica, sans-serif;
    }
    p{
        font-size:16px;
        text-align: center;
        line-height: 60px;
        font-weight: 700;
    }
    
    .cards{
        max-width: 80%;
        background-color: rgba(255, 255, 255, 0.151);
        border-radius: 20px;
        margin:auto;
        margin-top: 5%;
        padding:1%;
        box-sizing: border-box;
        box-shadow: 0px 2px 18px 0px rgba(255, 255, 255, 0.39);
        border-color:white;
        border-style: solid;
        border-width: .2px;
    }
    
    .header{
        margin-top:20%;
        position: absolute;
        top:-28%;
        Left:14%;
        width: 72%;
        height:26%;
    }
    
    #title{
        padding:2%;
        text-align: center;
        margin:auto;
        padding-top:1%;
        width:100%;
        height:20%;
        font-size: 80px;
        color:white;
        font-weight: 700;
    }
    #sub_title{
        text-align: center;
        margin:auto;
        margin-top:7%;
        margin-bottom: 1%;
        font-size: 20px;
        color:white;
        letter-spacing: 5px;
        font-weight: 300;
    }
    
    .data_container{
        width:80.4%;
        position: relative;
        margin: auto;
        margin-top:14.5%;
        display: flex;
        flex-direction: row;
        flex-wrap:wrap;
        color:white;
    }
    .left{
        display: flex;
        width:18%;
        height: 400px;
        margin-top:10%;
    }
    .middle{
        position: relative;
        width:68%;
        height: 400px;
        margin-top:10%;
        margin-left:1%;
    }
    
    #diagnose_container{
        text-align: left;
        margin-top: 5.8%;
        margin-left: 5%;
        font-size: 20px;
        display: flex;
        flex-direction: column;
        flex-wrap:wrap;
        color:white;
    }
    
    #wheel_data{
        margin-top:50%;
        height:40%;
        width:100%;
        padding:28px;
        margin-left: -20%;
        padding-top:20%;
        padding-bottom: -100%;
    }
    .numbers{
        font-size: 6rem;
        line-height: 120px;
        font-weight: 700;
    }
    
    #main_data_container{
        text-align: left;
        margin-top: 1.7%;
        margin-left: 5%;
        font-size: 20px;
        display: flex;
        flex-direction: column;
        flex-wrap:wrap;
        color:white;
    }
    #total_distance{
        position: absolute;
        top:34%;
        left:30%;
    }
    #total_distance_number{
        position: absolute;
        top:15%;
        left:57%;
    }
    #total_dist_data{
        position: absolute;
        top:-55%;
        left:-10%;
        margin-top:32%;
        height:40%;
        width:100%;
        padding:28px;
        margin-left: 8%;
        padding-top:20%;
        padding-bottom: -100%;
    }
    #sect_dist_data{
        position: absolute;
        top:-10%;
        left:-13%;
        margin-top:32%;
        height:40%;
        width:100%;
        padding:28px;
        margin-left: 8%;
        padding-top:20%;
        padding-bottom: -100%;
    }
    #section_distance{
        position: absolute;
        top:28%;
        left:32%;
    }
    #section_distance_number{
        position: absolute;
        top:8%;
        left:60%;
    }
    
    #wheel{
        position: absolute; 
        left: 6.5%;
        top: 39%;
        height: 20%; 
        width:auto;
    }
    #section{
        position: absolute; 
        left: 34%;
        top: 17%;
        height: 18%; 
        width:auto;
    }
    #whole{
        position: absolute; 
        left: 31.5%;
        top: 28%;
        height: 12%; 
        width:auto;
    }
    #logo_left{
        position: absolute; 
        left: 23.5%;
        top: 13%;
        height: 40%; 
        width:auto;
    }
    #line{
        position: absolute; 
        left: 9%;
        top: 50%;
        height:.4px; 
        width:82%;
        background-color: white;
        box-shadow: 0px 0px 0px 0.5px rgba(255, 255, 255, 0.5);
    }
    
    </style>
    <!-- <link href="https://fonts.googleapis.com/css?family=Paytone+One&display=swap" rel="stylesheet"> -->
  </head>

  <body>

    <div class="header cards">
        <div id="title">Black Box 2.0</div>
        <!-- <img src="https://i.ibb.co/D151XcN/logo.png" alt="logo" id="logo_left"> -->
        <div id="sub_title">Tracker Data</div>
    </div>

    <div class="data_container">
        <div class="left cards">
            <div id="diagnose_container">
                Diagnose Data
                <!-- <img src="https://i.ibb.co/pwz5f1h/wheel.png" alt="wheel" id="wheel"> -->
                <div id="wheel_data">
                    <p>Wheels Rotation:</br>
                        <span id="life_time_rotations" class="numbers">0</span>
                        times
                    </p>
                </div>
            </div>
        </div>
        <div class="middle cards">
            <div id="main_data_container">
                Main Data
                <div id="total_dist_data">
                    <!-- <img src="https://i.ibb.co/wrP22nX/whole.png" alt="whole" id="whole"> -->
                    <p id="total_distance">Total Distance:</p>
                    <p id="total_distance_number">
                        <span id="lifetime_dist" class="numbers">0</span>
                        km
                    </p>
                </div>
                <div id="line"></div>
                <div id="sect_dist_data">
                    <!-- <img src="https://i.ibb.co/RDxLXdW/section.png" alt="section" id="section"> -->
                    <p id="section_distance">Section Distance:</p>
                    <p id="section_distance_number">
                        <span id="section_dist" class="numbers">0</span>
                        km
                    </p>
                </div>
            </div>
        </div>
    </div>

    <script>

    // calculates total distance in km given number of wheel rotations
      function dist_calculator(rotations) {
          const wheel_size = 10; // in cm
          const pi = 3.14;
          return rotations * wheel_size * pi / 100000;
      }

      setInterval(function () {
          console.log("getting data");
          // Call a function repetatively with 2 Second interval
          updateLifetimeData();
      }, 2000); //2000mSeconds update rate
      
      function updateLifetimeData() {
         console.log("requesting lifetime data");
        var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function () {
              console.log("got lifetime data response back");
              if (this.readyState == 4 && this.status == 200) {
                  var lifetime_rotation = this.responseText;
                  var lifetime_dist = dist_calculator(lifetime_rotation);
                  document.getElementById("life_time_rotations").innerHTML = lifetime_rotation;
                  document.getElementById("lifetime_dist").innerHTML = lifetime_dist.toFixed(2);
              }
          };
        xhttp.open("GET", "readLifetime", true); // <-- change on server
        xhttp.send();
      }
      
    </script>
  </body>

</html>
)=====";
