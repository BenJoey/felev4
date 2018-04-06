with Card_Dir;
use Card_Dir;
package Coords is
   type Coord is private;

   function Get_X(C: Coord) return Integer;
   function Get_Y(C: Coord) return Integer;
   procedure Set_X(C: in out Coord; I: Integer);
   procedure Set_Y(C: in out Coord; I: Integer);
   function Get_Distance(C:Coord; D: Coord) return Integer;
   procedure Change_To_Direction(C: in out Coord; Dir:Cardinal_Direction);

   generic
      type Item is private;
      type Map is array(Integer range <>, Integer range <>) of Item;
      function Coord_With_Array(C:Coord;Matrix:Map) return Item;

private
   type Coord is record
      x,y: Integer;
   end record;
end Coords;
