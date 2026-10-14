ser = serialport("/dev/cu.usbmodem64E833692FDC2", 115200);

X = [];
Y = [];
Z = [];
figure;

while  true
    line = readline(ser);
    parts = split(line, ",");
    pan = str2double(parts(1));
    tilt = str2double(parts(2));
    distance = str2double(parts(3));

    if distance > 0 && distance < 5000
        panRad = deg2rad(pan);
        tiltRad = deg2rad(tilt);
        x = distance * cos(tiltRad) * cos(panRad);
        y = distance * cos(tiltRad) * sin(panRad);
        z = distance * sin(tiltRad);
        X(end+1) = x;
        Y(end+1) = y;
        Z(end+1) = z;
        scatter3(X,Y,Z,10,Z,"filled");
        axis equal;
        drawnow;
    end
end

      