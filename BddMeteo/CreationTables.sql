CREATE SCHEMA IF NOT EXISTS `meteo` DEFAULT CHARACTER SET utf8 ;

DROP TABLE IF EXISTS `meteo`.`MesuresExterieures` ;

CREATE TABLE IF NOT EXISTS `meteo`.`MesuresExterieures` (
  `idMesuresExterieures` INT NOT NULL,
  `horodatage` DATETIME NOT NULL,
  `idStation` INT(3) NULL,
  `batterie` VARCHAR(3) NULL,
  `temperature` DECIMAL NULL,
  `humidite` INT(3) NULL,
  `vitesseVent` DECIMAL NULL,
  `directionVent` INT(3) NULL,
  `rafale` DECIMAL NULL,
  `pluie` DECIMAL NULL,
  UNIQUE INDEX `idMesuresExterieures_UNIQUE` (`idMesuresExterieures` ASC),
  PRIMARY KEY (`idMesuresExterieures`))
ENGINE = InnoDB;


