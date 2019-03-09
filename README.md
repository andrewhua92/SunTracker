# ECEDD-19
An Arduino Project for University of Waterloo's ECE 2023 Design Day

In a team of four (Andrew Hua, Huanyou Wei, Darryl Wu and Jason Zhang), we worked together on creating a device that could
track light. Using photodiodes, an Arduino UNO, various circuitry, and Tetrix kits, we built a free-standing, rotating arm that
moves based on the amount of light which is being detected by the photodiodes.

![Device](https://github.com/andrewhua92/ECEDD-19/blob/master/ECE_DD_Device_'19.jpg)
(Rotated on it's side; sorry about this)

The premise of the design was to absorb as much energy as possible by the sunlight, moving the arm (with the solar cell attached
to its end) based on the amount of light the individual photodiodes were receiving. The rotation of the arm utilized a standard
rotational servo which moves based on angular analog inputs.

The code was done in C++ in an Arduino IDE. The primary algorithm was a State Machine that would determine the current state of
the photodiodes and move based on how much light is being detected. As the values being read in were analog, we were able to
determine the threshold values of ambient light and light that is being projected on from a light source (i.e a sun or a lamp).

Placed in the top 5 (ranking based off of amount of energy absorbed by solar cell attached to device).
