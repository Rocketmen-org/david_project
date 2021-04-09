To run, simply type "make", and then "./my_game".

To walk around, press either the left or right arrow keys to move left or right respectively.
	You can hold down a key to keep moving in that direction.

To jump, press the up arrow key.
	Once you commit to a jump, you can't change direction. Don't try, you'll hurt yourself.
		Just like real life.
		
To quit just click the 'x' at the top corner of the screen.

For my movement, I wanted to do one as a pos metaphor, and one as a vel metaphor.
The movement is pos-delta and the jump is vel-delta.

The movement isn't normal pos, because every object has the potential to move a different step value. (ex: x_stepsize variable) 
You're also able to hold down a key to make a continuous run.
The jump is vel-delta, because it is controlled by a velocity that changes based on where the object is in the jump. 
Eventually, it will move down, and if I ever get to implementing a variable ground level, then it will continue to fall 
at terminal velocity until it hits the ground.

Interestingly enough, I believe implementing one movement as a position metaphor and another as a velocity metaphor, 
makes the movement quite choppy and they don't mix well. I want to change the movement to a velocity or 
velocity-delta metaphor at some point... lesson learned.
