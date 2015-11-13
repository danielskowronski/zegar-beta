difference(){
  difference(){
    //base
    linear_extrude(height = 60) 
      polygon( [
        [0,0],  [-70,0], [-70,20], [-35,55], [0,55], 
        [-2,2], [-68,2], [-68,19], [-34,53], [-2,53]
      ] ,[ [0,1,2,3,4],[5,6,7,8,9] ]  );

    //screen hole
    translate ([0,0,10])
      linear_extrude(height = 40) 
        polygon( [  
          [-62.5,24.5], [-64.5,25.5], [-40,50], [-38,48.5] 
        ] );
  };

  //joystick hole
  translate ([-35/2,50,30])
    rotate([0,-90,-90])
      linear_extrude(height = 10) 
        circle(d = 25);
}