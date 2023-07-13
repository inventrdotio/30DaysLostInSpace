DAY 2
 
Greetings from Rescue shuttle control our Telemetry indicates that you
succeeded in starting up your Hero controller and are ready to start working
with it! That's great news that's the first step in getting your shuttlecraft
functional and ready to get you home.

One of the first things that you're going to need to do is learn how to turn on
the lights in your shuttle and how to control the various functions on board.
Doing that is going to involve developing some knowledge both of analog
circuits and of the digital computer control that's provided to you by your
hero. so we're going to walk through the basic use and the basic concepts of
both of these functions. during today's session and by the end of today's
session we hope you'll have the lights on. 

You'll notice that in addition to the hero device, that you've got in your
shuttle which connects to your ship's computer through the USB cable, you have
a white rectangular plastic board, this thing called a breadboard its purpose
is to allow you to quickly and easily assemble circuits from discrete
components. And by discrete components I mean things like what we have here
resistors light emitting diodes wires and we will discuss what those components
are and how they're used very soon, but I first wanted to sort of show you the
breadboard that we'll be using in addition to the Hero controller. 

Now let's back up for a moment and talk a little bit about circuits, analog
circuits, a circuit is a path or multiple paths through which electricity can
flow around in some sort of a controlled and closed loop it's somewhat like
water flowing around through pipes or hoses. now in order for a circuit to
function, the circuit must be completed in a in a complete circuit and that's
rather similar to the idea that in order to get water to flow around in a in a
hydraulic circuit. We need to make sure that all the water containing or water
channeling devices are connected end to end and so in order for water to flow
around a circuit it's not just sufficient to have a complete circuit but we
also have to have some pressure provided. 

In order to make it move the higher the pressure the more water will move
through the pipes per unit time and so the greater the flow rate will be.
however at a given pressure more water will flow through a larger diameter pipe
and less water will flow through a smaller diameter pipe and in our analogy to
electric circuits, the voltage or another word for voltage is potential that's
provided Say by a battery or a power supply is similar to the water pressure
in. 

In our water example and similarly to the idea that some pipes have greater
resistance to flow and some have less resistance to flow depending upon how
wide the pipe is, we have conductors of electricity that have greater
resistance or less resistance so we call a device like this one right here
that's designed to have a specific resistance to the flow of electricity. A
resistor logically enough and so a high value resistor with a large resistance
would be similar to a pipe with a narrow diameter that restricts the flow of
water and a low value resistor would be analogous to a wide pipe with a low
resistance to flow. 

Now if we want less currents to flow through a circuit for example, we would
naturally insert a resistor that had a high enough value of resistance to
reduce the amount of current to an acceptable level and we can figure out how
much current will flow through a resistor by taking the voltage applied that's
like the pressure in water and dividing that by the resistance. So as an
example, our hero right here is able to supply for us a voltage of five volts,
there's a slot right here a pin on the here that's labeled 5V that corresponds
to 5 volts. 

We also have here some resistors like this one or the one that's currently
connected to the breadboard. Right here it has a resistance of 220 ohms, so if
I want to send current through this resistor using my potential of 5 volts the
current that would flow would be 5 divided by 220. So if you calculate what
that value is 5 divided by 220 is .023 amperes so that turns out luckily for us
to be just about the right amount of current necessary to illuminate this
device which is a light emitting diode. It's like a light bulb but unlike an
incandescent light bulb, it doesn't function by heating up, it functions by
converting electrical energy into light. 

So we wouldn't want to send too much current through our LED because if we did
that we might be at risk of burning it up. Knowing the proper value of
resistance to put into our circuits to limit the amount of current is pretty
important, so this is already something valuable that we've learned about these
circuits and one of the basic ideas that we'll want to understand in order to
design our own circuits. 

But now before we go any further with that we have a little bit more to learn
we want to not only be able to put together an analog circuit and have current
flow through it of a desired amount, but we also want to be able to control our
Circuit by giving instructions to the hero through our computer.

Now it turns out that by writing correctly constructed code we can tell the
hero how and when to apply voltages to certain places. On the hero board and
use that to say illuminate a light emitting diode, now let's go ahead we are
we're going to talk about how to construct that code and how to command the
hero in a moment. But first of all, let's talk a little bit more about
connecting our circuit together and connecting it to the hero one way to
connect circuits together is with wires like the wires that we have right here. 

But if we have to solder everything together permanently, this can be very
tedious and time consuming and it's also inconvenient if we want to change our
circuit. So for example if we want to revise it and we have a new idea we want
to try, a new design so the breadboard here is there to make this job much
easier because instead of having to permanently solder components together, we
can just connect Parts together end to end by pushing their ends into the holes
on the breadboard. 

The pins of our components fit right into the holes of the breadboard. The
reason why that's helpful is that the breadboard provides electrical
connections between holes in the same row, so for example all of the holes here
in row six are connected together electrically or all the holes in row five
turns out we've also got connected holes in vertical lines as well. This red,
it's red and this blue vertical line are also connected and although we won't
use those today we'll find that it'll be convenient for us in the future to be
able to use both the horizontally and the vertically connected rows of
terminals. 

For now though, what we're going to do is illustrate how we might use the
breadboard and the 5 volts provided by the hero to illuminate a light bulb or a
light emitting diode. So I mentioned before the slide, emitting diode can emit
light when current flows through it and unlike an incandescent light bulb a
light emitting diode only works properly when current flows in one particular
direction that is in through the long prong and out through the short prom. A
way of remembering that, is that you need to connect the longer prong to the
higher voltage that would be to the 5 volt side and then the shorter prong to
go to the low voltage side or zero volts. 

So let's see if we can use the breadboard to connect this led to a source of
voltage and get it to illuminate. now as I mentioned before there is a pin on
the hero labeled 5V for 5 volts so we're going to take the wire and connect it
to that 5 volt pin and then connect that wire in turn to a particular row. here
on the breadboard and this particular case, I've chosen to connect it to row
number six it's nothing important about that just pick that at random also
connected to row six is one side of this resistor. 

This 220 Ohm resistor if I were to then connect another wire from here back to
zero volts or ground round is a another shorthand name for zero volts in. this
circuit then I would have current flowing through the resistor in a circuit
that wouldn't be too useful because the current really wouldn't be doing
anything, so rather than simply sending a wire back to ground here, I'm going
to send the current through the LED and see if we can get the LED to light. 

So let's connect the long end of the LED to row 10. like so and it just so
happens that the short end of the LED where the current will be flowing out is
connected to row 11. so if I take one more wire and connect that to row 11. 

I'm almost ready to see the light come on all I need to do is complete the
circuit by connecting this wire to ground to zero volts. so let's give that a
try and sure enough the light comes on. so that's pretty exciting we've now
figured out how to turn the lights on when I have a complete circuit from zero
volts. so far rather from 5 volts to zero volts passing through the resistor
and through the LED, I am producing light so that's progress but now what we'd
like to do is get the hero involved in an intelligent way.

We'd like the hero to take over the job of connecting and disconnecting the
voltage to our circuit and so that's our next step right now, so we will for
the moment disconnect our circuit and shift our attention for the moment to the
hero. and how we can control the hero now, what we have I will direct your
attention next to our code window what you see here is that the code that is
Illustrated in this window has a particular sort of structure to it. a sort of
syntax to it what we'll find an intelligent way. 

We'd like the hero to take over the job of connecting and disconnecting the
voltage to our circuit and so that's our next step right now. So we will for
the moment disconnect our circuit and shift our attention for the moment to the
hero and how we can control the hero now what we have I will direct your
attention next to our code window what you see here is that the code that is
Illustrated in this window  actually command the hero to do something
interesting. 

In our case what we want to command the hero to do is to provide voltage to
particular locations on the hero board. All right so let's get started with
with some code. The first thing that we need to do is we need to define a
variable, and in order to do that I'm going to put a preliminary statement up
at the top of this code window and the preliminary statement is defining a
variable called light. This is just a number an integer and I've chosen to give
light the value of Yourself included who's trying to read this code and
understand what it's doing. 

So you should be getting into the habit of writing useful comments whenever you
write code, because it will be a very helpful way of telling someone else what
you're trying to do with your code or it may be a helpful reminder to yourself
when you come back later and try to remember what you were doing. So keep in
mind that comments are very important and we'll try to use those comments as
much as possible. 

All right so right now get to in a little while is designed to run repeatedly
over and over again and will not stop until you turn the hero off, so let's get
started by putting some statements into setup! What I'd like to do is the
following I want to use a command called pin mode. Let's go ahead and type pin
mode in so that we have an idea what it looks like foreign mode takes as its
first input right here a variable in this case light so we know that we're
telling pin mode I want to do something with pin number 12. 

Another following the pin mode and its semicolon is another statement. Digital
right now does something to that pin in this case pin 12. and what it says is
set its voltage to low, low is just another way of saying zero volts so when we
see, you're going to see 5 volts and when we see low we're going to have zero
volts. Now actually since we'd like to turn the LED on, let's change from low
High and that way when this is executed pin 12 will. Now be at 5 volts and that
could be very useful to us so let's go ahead and the light comes on. 

So we've now succeeded in turning on the light but without actually touching
the circuit, we've allowed the hero to do that for us and we can change the
status, if we want if we change the code from saying voltage High to voltage
low, or zero volts we should now have no current flowing. And so if I upload
the code now, the LED goes off so that's that's some good progress. We've now
succeeded not only in turning on the LED but controlling the LED being on or
off by giving commands through the code. 

And you paste it in you'll notice by the way while I'm doing this that we did
have an appropriate comment in setup. We said that we are initializing the
digital pin, in this case pin 12 to set its value to high. Now what we're going
to do. In New is we're going to change the status, and we're going to do this
repeatedly as long as the hero is turned on. 

So the first statement in, does something that might seem a little pointless
and that is it says change the value of light to zero volts to low. Well
milliseconds or in other words one half of a second, and then this whole
sequence will just repeat. So if you think about it now for a moment when I run
this what it should do is wait for one second then turn the light on. Leave the
light on for half a second and then turn the light off again. 

And do that repeatedly blinking the light on and off off for one second on for
half a second. So let's check and see if when we upload our code if it
functions in the way we expect it to. So right now, we can see there's no light
on. Let's upload our new of time so let's change it to a tenth of a second or
100 milliseconds.

Okay so that's my new code so if I re-upload that to the hero, it should change
the rate of flashing. Let's see if that works okay, upload and here we go
two-second weight 10th of the second Flash well. 

I think you can see now how we are able to use the controls of the hero to
control our analog circuit and do something mildly interesting with the lights
here flashing them on and off in a specified pattern and  if you wanted.

You could probably experiment a little bit on your own you might be able to
write yourself some code that will flash out a message in Morse code, or do
something else that might be interesting in terms of turning the lights on and
off. In some specified way but for now we've been able to demonstrate and work
out the basics of both an analog circuit and its digital control and that's
just exactly what we wanted to do.

In this session so for now, you can go ahead and practice with this and we'll
sign off for now and next time we'll see if we can do something even more
interesting using our breadboard and our Hero controller. So for now remember
events safe and we'll see you next time!

