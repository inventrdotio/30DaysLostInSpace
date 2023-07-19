DAY 3

Greetings once again from rescue shuttle control. We've noticed in our
telemetry that you have succeeded in getting your lights turning on and off. So
that's great news, because it means that you're well on your way to getting
your systems up and running. 

We're going to continue working on today's session with learning how to
construct circuits and control them with your hero controller, and we're going
to build on what we learned in the last session. So today what we're going to
do, is try and give you a little more flexibility in controlling your lighting.
We've noticed that Some of your power levels are dropping and you need to be
able to turn those lights on and off when you don't need them. 

So in order to do that we're going to involve Some switching in today's
activity. We do have a switch as a part of our discrete components, you may
have noticed this before we have this little device that you can take a look at
here it's called a dip switch and dip is an acronym dip stands for dual inline
plastic and that name is Sort of logical you can see that it is like many
electronic components in a little plastic package. It has two rows of pins in
line with one another, So that explains the name dual inline plastic. 

This particular device is a set of switches you'll notice that there are
actually three switches built in to one device here. So we could in principle
use this to control three separate circuits. Although today we're only going to
use one of them. Switch number one, which you'll see is indicated with the one
on top of the device right here. We'll Soon find out that when the switch is
flipped from the off to the on position, like So then the pins on opposite
sides in that row are connected and you have a complete circuit, So we're going
to use that today. 

Now the last time we worked with the hero we basically were controlling
outputs. We were asking the hero through the code that we wrote to either
switch a high voltage, or a low voltage to a particular pin as an output. We're
going to continue with that today, but we're going to add an additional
function today this time we're going to have the hero not only controlling
outputs on certain pins but we're alSo going to have it accept input from us.
The input that it reads on whatever pins we specify will cause the hero to take
the actions that we program it to take. 

So we're going to add that additional function today both in terms of the way
we build our analog circuit and in terms of the way that we program and write
code for the hero. So let's direct our attention for a few moments to our
breadboard and hero and look at Some of the circuit building that we need to
do. 

Today, if you look at the upper part of the breadboard, you'll recognize what
looks like a fairly familiar circuit from last time. You'll notice that we have
a circuit that begins on pin 12 and you remember that last time we were able to
ask the hero to connect pin 12 to 5 volts. When commanded and So from that we
connect to a row on the breadboard in this case it happens to be alSo row 12.
Wouldn't have had to be row 12 though, it could be any place we conveniently
wanted to build the circuit from that connection on pin 12. 

We passed through a current limiting resistor and you'll remember from our
discussion last time that we've chosen the value of this resistor to give an
appropriate amount of current to light our led light bulb. The current after
passing through this resistor passes into the positive terminal of the led lamp
and we've positioned it So that the current will come out of the lamp on row
11. Just above there. 

Now in order to complete the circuit we're going to have to provide a return
path back to ground. So this green wire right here takes us around and down to
a row on the column rather on the breadboard that's labeled with a blue line.
Here and then onward from that to ground on the hero you might wonder why
didn't we just go directly from row 11 to ground and we certainly could have
done that but we're anticipating that we're going to need to build another
circuit in a little while that will alSo want to have zero volts access or
ground. 

So we've chosen to make this entire blue column right here zero volts by
connecting it to ground on the hero and then any time we want to get zero
volts. We can connect to anywhere on that blue column So far that looks like a
pretty familiar analog circuit to us, and all we need to do is ask the hero to
supply 5 volts to pin 12 and our lamp should go on. 

Now what we want to do in today's exercise is figure out a way of turning the
light on and off without having to re-upload the program to the hero every
time. And we're going to do that using this DIP switch. 

Now you might think that all we'd want to do is just take the switch and put it
in series with the circuit that's carrying current through the land, that would
be one way to do it but we want to have a little more flexibility in the way
that we can control this. So rather than directly interrupting the circuit and
the current that's passing through the lamp, we're going to control the hero by
supplying it with an input. 

So in order to see how we're going to do that it's time . Now for us to switch
our attention over to the code window and see how we're going to handle this.

As we look at the code window, you'll see we have a couple of empty routines
here. The setup routine and the loop routine which we're about to populate with
some code. We've also got a variable led for our light emitting diode that has
been assigned our traditional value of 12. So when we identify led is 12 it
means that when we set the voltage on that pin high, the light will go on.

Now what we're going to need is another variable and this is going to be a
variable that we will use to command the hero through our switch and so what
we're going to do is define another variable and we'll name that one switch
one. You'll notice that we have a comment next to this just to remind us that
you're setting switch 1 equal to 2, which means that pin 2 will now be the pin
on the hero that we're going to connect to our switch.

Now we have to ask ourselves well, what are we going to do with that pin 2,
that's different from what we did say with pin 12, and in order to understand
that we want to see what we're going to do in the subsequent setup and loop
functions. On our hero. So the next thing we'll do is place some code in setup
and analyze what it's doing you'll notice that our comment right now says that
we're going to set up both an output and an input on the hero.

We are now once again using pin mode and in the first of these two statements
you'll notice that pin mode is very familiar to us. It's just like we used it
last time we're taking led which is 12 and we're setting its function to be an
output so that when we command it we can cause led or 12 to be either high or
low in contrast. We're going to use pin mode to make switch have a function of
an input. The hero is not going to cause input to change, Hero is going to
watch that input and take cues from its value. So that when we cause input to
change the hero will take appropriate action.

All right. So that's our setup but now what are we going to do with that well
the real action is now going to be taking place in our loop and so here's where
we will see something quite different from what we have done before. So let's
go ahead and put a block of new code into loop and talk a little bit about what
it's doing. I've got a couple of comments here i'm making note here that within
loop we're taking repeated actions, but these are now going to be actions that
are based on the status of the value of switch one, that is the voltage that is
being applied to pin two.

Now the next thing that happens in loop is something new. We're going to apply
a conditional test, we're going to ask the hero to check what is the voltage on
pin two or in other words switch one if digital read of that switch of pin two
is equal to high. Then take the action contained within these curly brackets
which is our usual action of turning on the led on pin 12. So in other words,
set led to high. So the light will go on but now this is a conditional, it's
only taking place if switch one is high.

On the other hand if it's not high, in other words if it's low or zero volts
then set digital write led to low. In other words turn the led off. So what
this means now is that depending upon whether or not switch one is high or
switch one is low, you will either have the led go on or off and we can control
that.

All right, hopefully that's fairly clear our circuit. On the breadboard is not
quite ready to work with this code yet. We're going to have to set up a way of
setting the value of pin 2 or switch 1 to either high or low depending on what
we want. So what we're going to do returning over here to the to the breadboard
is take our our DIP switch and place it so that the first of the three
switches, switch one is spanning across the gap here in the breadboard.

So that when the switch is in the off position, these rows on the left are not
connected with these rows on the right. But for example if I take the switch
and I flip it to on, like so let's get that switch on. Now you can see our our
first switch here is lined up with row number 23 on the breadboard and now
there will be a complete connection from the left hand to the right hand side
of row 23.

If I switch it back to off then there will be no connection, now this is part
of the progress that we want to make but the next thing that we have to do is
to provide a source of five volts that we can either connect or not connect to
pin number two, which is going to be our input to the hero.

So here I have a long wire that I connected to five volts on the hero I'm going
to bring it over here and connect it up to the right hand side of row 23 like
so. Now with the switch in the off position that's not going anywhere. There's
no completed circuit and the side of row 23 is still at an indeterminate
voltage level.

On the other hand, if I were to switch this to on the current, can now flow
through the switch through this second resistor and down to ground. You'll
notice that I'm now using the same ground convenient ground bus that i'd used
earlier on constructing the analog circuit above, so with the switch in this
position I now have a complete circuit, and the voltage on the upper side of
this resistor will be at five volts relative to zero volts on ground right
here.

So if I take this green wire and connect it to pin number two which we've named
switch switch one, now I have a signal that I can send to the hero when this
switch is in the off position. The voltage on this green wire and therefore on
pin two is zero. And when the switch is in the on position like, so now the
voltage on the green wire and which is sent to pin 2 is high or 5 volts. So the
hero will be able to read that input and take appropriate actions on pin 12 and
turn the led on or off.

By the way, there's a detail of our switch circuit that may bear a little
explaining. So let's dive into it in a little bit more detail. 

You may be wondering why we need to have a resistor between the switch and the
hero board in our circuit. And perhaps the best way of explaining is to examine
what would happen if we didn't have that resistor. So, Iâ€™ll direct
your attention to this diagram that shows us what the circuit would look like
if we tried to connect and disconnect 5 volts to our hero input, with just a
switch. 

So, what we have here right now is a diagram that shows the switch in the open
position. That is, 5 volts is not connected to the other side of the switch. In
this case, you can see that the hero input our input pin is connected by wires
directly to ground that is to zero volts. So there's no ambiguity there, the
hero should see a signal of zero volts or low when the switch is open. So
that's not too surprising, and it would seem as though this would be a
perfectly fine way to wire up the circuit. 

Now, let's look at what happens if we close the switch. If we close the switch,
we now, have a sort of a strange situation because the hero's input is
connected by wires both to 0 volts and to 5 volts. So what is the voltage
recorded at the hero input? It's really not determinate because we can't really
have this be at two different voltages. 

In fact, if we tried to do this, if we tried to connect five volts to ground
without any resistor in between, the current that would flow would be huge,
probably more than the current that the hero can actually supply. This would be
a short circuit, and it has the other undesirable effect of providing or
producing a voltage here at the hero input pin which is indeterminate, we just
don't know what it would be. 

So this would be a poor way to design our circuit. It wouldn't work as we wish
it to. So instead, what our solution is is place a current limiting resistor,
in this case, a 220-ohm resistor, between the hero input and ground. 

You'll notice that in this state with the switch open we still have the hero
measuring a voltage of 0 volts on its input. We can see that because we can see
a path that connects from ground to the hero input. Since there is no current
flowing, there is no voltage difference between the two sides of the resistor,
it's zero volts on this side, zero volts on this side. So the hero sees zero
volts. 

Now, unlike in the previous case when there was no resistor, when we close the
switch, we now have current flowing from 5 volts to ground through the 220-ohm
resistor. The amount of current, if we wanted to know what that would be, would
be 5 volts divided by 220 ohms. The important point for us to note now however
is that since there is a current flowing through this resistor. There's a
difference in voltage between this side which is connected directly to 0 volts
or low and the other side of the resistor which is connected directly by wires
to 5 volts. 

We can see that our hero, there's now no ambiguity about what the voltage is on
the hero input pin. It's 5 volts, and so we have exactly what we need, that is
an input which is 0 volts when the switch is open, and 5 volts are high, when
the switch is closed. And so that, in a nutshell, is why we want to design our
switch circuit with a resistor in this position. 

So with that, I think we're ready to go ahead and try uploading our code and
see if this will work as we designed it to.

So, we have our code constructed. Let's go ahead and upload it to the hero. We
would not expect anything to happen immediately because as we've set things up
right now, the voltage on pin two is zero, it's low, and so that means that
when we get to the conditional test it's going to the second of the two choices
which is turn the led off. 

So, let's see what happens now if we take our switch and flip it to on. And
there we go, we have now succeeded in remotely activating the circuit that
illuminates the led by providing a signal input into pin 2 of the hero. 

So this is yet another useful way of indirectly controlling the function of an
analog circuit and in this case, what we've had the hero do is make a decision
based on inputs provided to its input pin. So that's a pretty helpful
additional capability that we can now work into our subsequent projects and
designs. 

If you were so inclined, you could elaborate on this and do some additional
changes. Make some additional functions if you wanted, for example, all we've
done right here is simply caused the flipping of the switch to turn the light
on and off, which is almost indistinguishable from if I were to just put the
switch directly into the circuit itself. 

I could do something a little bit more interesting if for example I took the
code that is executed here when the if statement is true, that is when switch 1
is high. If I replaced that digital write with a series of commands similar to
those that we saw in our last session. 

So instead of just a single digital write, let's try this and figure out what
it's doing. It's saying digital write led low, wait for a second, digital write
led high, wait for a tenth of a second, low wait for a tenth of a second, high
wait for a tenth of a second and then repeat. 

So it looks like what we're going to have now when we flip the switch on is a
flashing sequence where first we'll have the led off for a second then on for a
temp of a second off for 10th of a second on. Again for a tenth of a second and
then repeat. So it'll be a double fast flash followed by a long pause.

So, let's see if that works, let's go ahead and re-upload our code once again.
There's nothing happening until we flip our dip switch into the on position and
when we do that, we now have a function that we can control with a single flip
of the switch. 

Which will execute a more complicated sequence of flashes. So you can try doing
some of your own experiments and modifications of this kind, as you get used to
controlling your lights conserving your battery power. We hope and start
looking into some of the other parts of your rescue shuttle that are perhaps
dark right now. 

And as we get more of the lights turned on and more of our functions going,
you'll be ready to tackle some more challenging problems. The next time I think
we're going to try and control more than just a single circuit and try our hand
at doing something even a little bit more complex. 

So go ahead and work on that, we'll continue watching telemetry here from
rescue shuttle control. Until next time when we have our next session together,
remember invent safe!

