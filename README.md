# Houdini-VEX-Butterfly-Curve
![alt text](https://github.com/ObeidaZakzak/Houdini-VEX-Butterfly-Curve/blob/master/butterfly_gold_front_low.png)

Here's a tutorial on how to make a butterfly pattern with `VEX`. Everything is done inside of one `AttributeWrangler` node. The following code is available inside of `vex_snippet.c` source file. You can also download the `.hipnc` file where everything is already done.

The Butterfly Curve equation was discovered by Temple Fay, ([Wikipedia](https://en.wikipedia.org/wiki/Butterfly_curve_(transcendental)))

We will use the parametric equations describing this pattern to build points with VEX :

![alt text](https://wikimedia.org/api/rest_v1/media/math/render/svg/6a17a33d739ede62a269949b5bf551a875397102)

![alt text](https://wikimedia.org/api/rest_v1/media/math/render/svg/92e1ec07900777c282b5c379b0877906f4594727)

![alt text](https://wikimedia.org/api/rest_v1/media/math/render/svg/3c9b54f7112ec2abd4125ef9b52aa55a9b8470ea)

## Getting started
All you need is to create a `Geometry` node and dive inside then create a `AttributeWrangler` node.

Then set the `Run Over` mode of the wrangler on `Detail (once only)`.

## User controls
Let's start by adding an integer channel to control the number of points to build :

```c
int nbPoints = max(1,chi('points_count'));
```

Using the `max` function helps to avoid division by zero as we are using `nbPoints` value to calculate our parameter step (that involves a division by zero).

(We will come back to add another control later for another parameter in the bonus section)

## Parameter for the parametric equations
Now let's define our variable `t` representing the parameter going from `0` to `12*PI`. The value of `dt` represents the step to add to `t` at each iteration of the `for loop` (that we will implement together).

```c
float t;
float dt = 12*PI / nbPoints;
```

## Useful variables for points creation
We still need to define some variables to store the point coordinates at each iteration :
```c
float x, y, z; // point coordinates
float factor;  // a value that we will calculate at each iteration
vector pts;    // the calculated point at each iteration
int points[];  // a list to store the points as we build them, so we can build edges later
```

## Calculating the coordinates
We are ready to start our `for loop` and calculate all the points of the butterfly curve. first, let's calculate the coordinates (by applying the two formulas in the beginning of the tutorial) :

```c
for (int i = 0; i < nbPoints; ++i)
{
    t = i * dt;
    
    factor = exp(cos(t)) - 2*cos(4*t) - pow(sin(t/12),5);
    
    x = sin(t) * factor;
    y = cos(t) * factor;
    z = 0;
}
```

We can now create points at each iteration :

```c
    pts = set(x, y, z);
    points[i] = addpoint(0, pts);
```

And when we have at least one point, we can create edges :

```c
    if (i>0) {
        addprim(0, "polyline", points[i-1], points[i]);
    }
```

We are done ! Now we have a plane butterfly curve !

![alt text](https://github.com/ObeidaZakzak/Houdini-VEX-Butterfly-Curve/blob/master/front.png)

## Bonus : bending the butterfly wings
A simple bend can be done by giving the `z` value something based on the `x` value. For example, the absolute value divided by a float.

Let's add another parameter channel in the user controls section :

```c
float r = max(1/1000,ch('bend'));
```

And now let's calculate the value of `z` based on `x` inside of the `for loop`:

```c
  z = abs(x) / r;
```

Now we can bend the wings of our butterfly curve by modifing the value of `bend` channel.

![alt text](https://github.com/ObeidaZakzak/Houdini-VEX-Butterfly-Curve/blob/master/perspective.png)
