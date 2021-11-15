#pragma once


struct ID {
    inline static int kMinAvaliableID { 3000 };
    inline static int depurationID    { kMinAvaliableID };
    static int getNewDepurationID() { return ++depurationID; }
    static void restartCountID() { depurationID = kMinAvaliableID; }
};