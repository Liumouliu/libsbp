extern crate byteorder;
extern crate crc16;

use self::byteorder::{LittleEndian,ReadBytesExt};
use std::io::{Read, self};
use ::messages::SBP;

const SBP_PREAMBLE: u8 = 0x55;

#[derive(Debug)]
pub enum Error {
    InvalidPreamble,
    CRCMismatch,
    ParseError,
    IoError(io::Error)
}

impl From<io::Error> for Error {
    fn from(error: io::Error) -> Self {
        Error::IoError(error)
    }
}

pub fn receive(a: &mut Read) -> Result<SBP, Error> {
    let mut preamble = [0];
    a.read_exact(&mut preamble)?;
    if preamble[0] != SBP_PREAMBLE {
        return Err(Error::InvalidPreamble);
    }
    let mut crc_state = crc16::State::<crc16::XMODEM>::new();
    let mut header = [0; 5];
    a.read_exact(&mut header)?;
    crc_state.update(&header);
    let mut header = &header[..];
    let msg_id = header.read_u16::<LittleEndian>()?;
    let _sender = header.read_u16::<LittleEndian>()?;
    let len = header.read_u8()? as usize;

    let mut payload = [0; 256];
    let mut payload = &mut payload[..len];
    a.read_exact(&mut payload)?;
    crc_state.update(&payload);

    let crc = a.read_u16::<LittleEndian>()?;
    if crc != crc_state.get() {
        return Err(Error::CRCMismatch);
    }

    Ok(SBP::parse(msg_id, &mut &payload[..]))
}