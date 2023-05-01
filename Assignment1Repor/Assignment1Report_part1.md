implemintation of Bresenham’s algorithm:
we sepirated the implemintation into cases, when dx/dy is over 1 or less than 1, or when dx/dy is negative.
all cases are built over the same basic structure .
the implemintation goes as follows :
int x1 = p1[0], x2 = p2[0], y1 = p1[1], y2 = p2[1];
    int dx = (x2 - x1);
    int dy = (y2 - y1);
    int x = x1, y = y1;
    int err;

    //if our line is on Y
    if (dx == 0) {

        if (dy > 0) {
            while (y <= y2) {
                PutPixel(x, y, color);
                y++;
            }
        }
        else {
            while (y >= y2) {
                PutPixel(x, y, color);
                y--;
            }
        }

    }


    //if our line is on X
    else if (dy == 0) {
        if (dx > 0) {
            while (x <= x2) {
                PutPixel(x, y, color);
                x++;
            }
        }
        while (x >= x2) {
            PutPixel(x, y, color);
            x--;
        }

    }

    else {
        float m; //m is our
        m = (float)dy / (float)dx;
        if (dy > 0) {
            if (m > 0 && m < 1) {
                err = -dx;
                while (x <= x2) {
                    if (err > 1 / 2) {
                        y++;
                        err = err - 2 * dx;
                    }

                    PutPixel(x, y, color);
                    x++;
                    err = err + 2 * dy;
                }
            }
            else if (m >= 1) {
                err = -dy;
                while (y <= y2) {
                    if (err > 1 / 2) {
                        x++;
                        err = err - 2 * dy;
                    }

                    PutPixel(x, y, color);
                    y++;
                    err = err + 2 * dx;
                }
            }
            else if (m <= -1) {
                err = -dy;
                while (y <= y2) {
                    if (err > 1 / 2) {
                        x--;
                        err = err - 2 * dy;
                    }

                    PutPixel(x, y, color);
                    y++;
                    err = err - 2 * dx;
                }
            }
            // if -1<m<0
            else if (m > -1 && m < 0) {
                err = -dx;
                while (x >= x2) {
                    if (err > 1 / 2) {
                        y++;
                        err = err + 2 * dx;
                    }
                    PutPixel(x, y, color);
                    x--;
                    err = err + 2 * dy;
                }
            }
        }
        else {
            // when a is between 0 and 1 and y is "-"
            if (m > 0 && m < 1) {
                err = -dx;
                while (x >= x2) {
                    if (err > 1 / 2) {
                        y--;
                        err = err + 2 * dx;
                    }

                    PutPixel(x, y, color);
                    x--;
                    err = err - 2 * dy;
                }
            }

            //when a is bigger than 1 & y is "-"
            else if (m >= 1) {
                err = -dy;
                while (y >= y2) {
                    if (err > 1 / 2) {
                        x--;
                        err = err + 2 * dy;
                    }

                    PutPixel(x, y, color);
                    y--;
                    err = err - 2 * dx;
                }
            }
            // when a is between 0 and -1 and y is "-"
            if (m < 0 && m > -1) {
                err = -dx;
                while (x <= x2) {
                    if (err > 1 / 2) {
                        y--;
                        err = err - 2 * dx;
                    }

                    PutPixel(x, y, color);
                    x++;
                    err = err - 2 * dy;
                }
            }

            //when a is smaller than -1 & y is "-"
            else if (m <= -1) {
                err = -dy;
                while (y >= y2) {
                    if (err > 1 / 2) {
                        x++;
                        err = err + 2 * dy;
                    }

                    PutPixel(x, y, color);
                    y--;
                    err = err + 2 * dx;
                }
            }
        }

    }

}




now i'll include sanity check results:
first sanity check, draw lines from a point to many points on a circles centered around the points:
![sanity_check](https://user-images.githubusercontent.com/80767830/200115155-06075203-947c-47c2-870a-493686f456d0.PNG)


second snity check, a simple circle:
![sanity_check_circle](https://user-images.githubusercontent.com/80767830/200115188-65d688e4-3ddb-430e-8b3b-2c31e51a6e5b.PNG)


and for last, some creative drawings:

1)
![sanity_check_2](https://user-images.githubusercontent.com/80767830/200115212-85d4cc5f-9fcc-44bc-9cfe-bf548ac11a55.PNG)


2)
![sanity_check3](https://user-images.githubusercontent.com/80767830/200115371-3d316418-6162-4398-86e2-0aa44f1cf962.PNG)












