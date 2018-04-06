package body Coords is
   function Get_X(C: Coord) return Integer is
   begin
      return C.x;
   end Get_X;

   function Get_Y(C: Coord) return Integer is
   begin
      return C.y;
   end Get_Y;

   procedure Set_X(C: in out Coord; I: Integer) is
   begin
      C.x:=I;
   end Set_X;

   procedure Set_Y(C: in out Coord; I: Integer) is
   begin
      C.y:=I;
   end Set_Y;

   function Get_Distance(C:Coord; D: Coord) return Integer is
   begin
      return ((C.x-D.x)**2+(C.y-D.y)**2);
   end Get_Distance;

   procedure Change_To_Direction(C: in out Coord; Dir:Cardinal_Direction) is
   begin
      case Dir is
         when N => C.y := C.y-1;
         when S => C.y := C.y+1;
         when E => C.x := C.x+1;
         when W => C.x := C.x-1;
         when NE => C.x := C.x+1;C.y := C.y-1;
         when SE => C.x := C.x+1;C.y := C.y+1;
         when NW => C.x := C.x-1;C.y := C.y-1;
         when SW => C.x := C.x-1;C.y := C.y+1;
      end case;
   end Change_To_Direction;

   function Coord_With_Array(C:Coord;Matrix:Map) return Item is
   begin
      return Matrix(C.x,C.y);
   end Coord_With_Array;
end Coords;
