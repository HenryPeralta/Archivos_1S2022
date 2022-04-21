package comandos

type MBR struct {
	mbr_tamano         int64
	mbr_fecha_creacion [19]byte
	mbr_dsk_signature  int64
	dsk_fit            byte
	mbr_partition      [4]Particion
}

type Particion struct {
	part_status byte
	part_type   byte
	part_fit    byte
	part_start  int64
	part_size   int64
	part_name   [16]byte
}
