//-----------------------------------
// Layers to render
//-----------------------------------

//layer_front(); 
//layer_mask();
//layer_diffusor();
//layer_grid();
//layer_cast();
//layer_support();
//layer_hollow();
//layer_middle();
//layer_back(0,0);

translate([0,0,20]) {
    %translate([0,0,15.1]) color("white",0.5) linear_extrude(3) layer_front();
    translate([0,0,14.9]) color("black",1.0) linear_extrude(0.1) layer_mask();
    translate([0,0,14.7]) color("white",0.5) linear_extrude(0.1) layer_diffusor();
    color("Goldenrod")  {
        linear_extrude(4) layer_grid();
        translate([0,0,-2.5]) linear_extrude(2.5) layer_cast();
        translate([0,0,-5]) linear_extrude(2.5) layer_support();
        translate([0,0,-7.5]) linear_extrude(4) layer_hollow();
        translate([0,0,-11.5]) linear_extrude(4) layer_hollow();
        translate([0,0,-15.5]) linear_extrude(4) layer_hollow();

        translate([0,0,-30]) linear_extrude(2.5) layer_middle();
       
        translate([0,0,-45]) linear_extrude(4) layer_hollow();
        translate([0,0,-47.5]) linear_extrude(2.5) layer_back(0,0);

    }
}

//-----------------------------------
// Configuration
//-----------------------------------

// Model size
model_width=114;
model_height=80;

// Grid config
grid_size = 8;
grid_step = 8;
grid_shift = 0.4;
grid_wall = 1;

// Height of the grid (widt of the wood)
wood_width=4;

// Holes radius (half of metric: M3, M4...)
hole_size=2; // M4

// Hole distance to edge
hole_distance=5;

// Minkowski radius
chamfer_size=4;

//-----------------------------------
// DO NOT TOUCH BELOW THIS LINE
//-----------------------------------

//-----------------------------------
// Components
//-----------------------------------

module hole() {
    translate([
        model_width/2-hole_distance,
        model_height/2-hole_distance,
        0
    ]) circle(hole_size, center=true, $fn=50);
}

module hole_ring() {
    translate([
        model_width/2-hole_distance,
        model_height/2-hole_distance,
        0
    ]) circle(5, center=true, $fn=50);
}

module base() {
    
    difference() {
        
        // Shape
        minkowski() {
            square([
                model_width-2*chamfer_size,
                model_height-2*chamfer_size
           ], true);
            circle(chamfer_size, $fn=50);
        }

        // Holes
        mirror([0,0,0]) hole();
        mirror([1,0,0]) hole();
        mirror([0,1,0]) {
            mirror([0,0,0]) hole();
            mirror([1,0,0]) hole();
        }

    }
}

module led_matrix_negative(type) {

    translate([
        grid_shift-grid_size*grid_step/2,
        -grid_size*grid_step/2
    ])
    for (x=[0:grid_size-1]) {
        for (y=[0:grid_size-1]) {
            translate([
                x*grid_step+grid_wall/2,
                y*grid_step+grid_wall/2,0
            ]) {
                square(grid_step-grid_wall);
            }
        }
    }

}

module switch() {
    square([8.2, 13.2], true);
}

module socket_hole(inside=0) {
    circle(inside ? 16/2 : 11.4/2, $fn=50);
}
module oled(type=0) {
    if (type==0) {
        square([28.4,27.6], true);
    } 
    if (type==1) {
        translate([0,27.6/2-1.5]) square([12,4], true);
    }
    if (type==2) {
        //translate([0,2.5]) square([27,15], true);
        translate([0,2.5]) square([25,13], true);
    }
}

module grid_eye(type) {
    
    // holes
    if (type==0) {
        translate([3-22/2, 3-31/2]) circle(2, $fn=50);
        translate([22/2-3, 3-31/2]) circle(2, $fn=50);
        translate([3-22/2, 31/2-3]) circle(2, $fn=50);
        translate([22/2-3, 31/2-3]) circle(2, $fn=50);
    } 
    
    // sensor
    if (type==1) {
        square([5.9,9.5], true);
    }
    
    // pcb
    if (type==2) {
        square([22,31], true);
    }
    
    // connectors
    if (type==3) {
        translate([3-22/2,0]) square([4,16], true);
    }
    
}

module button(type=0) {
    if (type==0) {
        circle(7/2, $fn=50);
    }
    if (type==1) {
        circle(10/2, $fn=50);
    }
}


//-----------------------------------
// Layers
//-----------------------------------

module layer_front() {
    difference() {
        base();
        //translate([27.0,-24.9]) socket_hole(0);
        translate([42.6,-24.9]) switch();
        translate([42.6,-7]) button(0);
    }
}

module layer_grid() {

    difference() {
        base();
        translate([-(model_width-model_height)/2,0])
            led_matrix_negative(1);
        translate([34,17.7]) oled(0);
        //translate([27.0,-24.9]) socket_hole(1);
        translate([42.6,-24.9]) switch();
        translate([42.6,-7]) button(1);
    }

}

module layer_mask() {

    difference() {
        base();
        translate([-(model_width-model_height)/2,0])
            led_matrix_negative(1);
        translate([34,17.7]) oled(2);
        //translate([27.0,-24.9]) socket_hole(0);
        translate([42.6,-24.9]) switch();
        translate([42.6,-7]) button(0);
    }

}

module layer_diffusor() {

    difference() {
        base();
        translate([34,17.7]) oled(2);
        //translate([27.0,-24.9]) socket_hole(0);
        translate([42.6,-24.9]) switch();
        translate([42.6,-7]) button(0);
    }

}

module layer_cast() {

    difference() {
        base();
        translate([-(model_width-model_height)/2,0])
            square(grid_size*grid_step+2, true);
        //translate([27.0,-24.9]) socket_hole(1);
        translate([42.6,-24.9]) switch();
        translate([34,17.7]) oled(1);
        translate([42.6,-7]) button(1);
    }

}

module layer_support() {

    difference() {
        base();
        translate([0, grid_step*(grid_size/2-1)])
            square([model_width-2*grid_size, grid_step*2], true);
        translate([0, -grid_step*(grid_size/2-1)])
            square([model_width-2*grid_size, grid_step*2], true);
        //translate([27.0,-24.9]) socket_hole(1);
        translate([42.6,-24.9]) switch();
        translate([42.6,-7]) button(1);
    }

}

module layer_hollow() {
    difference() {
        base();
        difference() {
            square([
                model_width-2*hole_distance,
                model_height-2*hole_distance
            ],true);
            mirror([0,0,0]) hole_ring();
            mirror([1,0,0]) hole_ring();
            mirror([0,1,0]) {
                mirror([0,0,0]) hole_ring();
                mirror([1,0,0]) hole_ring();
            }
        }
    }
}

module layer_middle() {
    difference() {
        base();
        grid_eye(0);
        grid_eye(3);
    }
}


module layer_back(transparent=0, holes=0) {
    difference() {
        base();
        if (holes) grid_eye(0);
        if (!transparent) grid_eye(1);
    }
}

