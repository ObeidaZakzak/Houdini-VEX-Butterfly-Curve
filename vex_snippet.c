// user controls
int nbPoints = max(1,chi('points_count'));
float r = max(1/1000,ch('bend'));

// parameter and parameter step
float t;
float dt = 12*PI / nbPoints;

// points coordinates
float x, y, z;
float factor;
vector pts;
int points[];

for (int i = 0; i < nbPoints; ++i)
{
    t = i * dt;
    
    factor = exp(cos(t)) - 2*cos(4*t) - pow(sin(t/12),5);
    
    x = sin(t) * factor;
    y = cos(t) * factor;
    z = abs(x) / r;
    
    // adding points
    pts = set(x, y, z);
    points[i] = addpoint(0, pts);

    // adding edges
    if (i>0) {
        addprim(0, "polyline", points[i-1], points[i]);
    }

}
