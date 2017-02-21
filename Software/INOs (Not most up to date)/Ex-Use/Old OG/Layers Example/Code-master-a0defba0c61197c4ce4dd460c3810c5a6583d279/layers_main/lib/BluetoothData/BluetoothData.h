#ifndef BLUETOOTHDATA_H
#define BLUETOOTHDATA_H

enum BluetoothDataType: int {
    motorSpeed = 0,
    motorRotation = 1,
    TSOP = 2,
    info = 3,
    none = 4
};

typedef struct BluetoothData {
    BluetoothDataType type;
    int value;
} BluetoothData;

#endif
