DROP TABLE IF EXISTS `path_trade`;
CREATE TABLE IF NOT EXISTS `path_trade` (`id` int(10) unsigned NOT NULL AUTO_INCREMENT,`station` int(10) unsigned NOT NULL,`product` int(10) unsigned NOT NULL,`profit` int(10) NOT NULL,`quantity` int(10) unsigned NOT NULL DEFAULT '1',`date` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,PRIMARY KEY (`id`)) ENGINE=InnoDB COLLATE='utf8_general_ci' CHARSET=utf8;

DROP TABLE IF EXISTS `product`;
CREATE TABLE IF NOT EXISTS `product` (`id` int(10) unsigned NOT NULL AUTO_INCREMENT,`category` int(10) unsigned NOT NULL,`name` varchar(255) NOT NULL,PRIMARY KEY (`id`)) ENGINE=InnoDB COLLATE='utf8_general_ci' CHARSET=utf8;

DROP TABLE IF EXISTS `product_category`;
CREATE TABLE IF NOT EXISTS `product_category` (`id` int(10) unsigned NOT NULL AUTO_INCREMENT,`name` varchar(255) NOT NULL,PRIMARY KEY (`id`)) ENGINE=InnoDB COLLATE='utf8_general_ci' CHARSET=utf8;

DROP TABLE IF EXISTS `station`;
CREATE TABLE IF NOT EXISTS `station` (`id` int(10) unsigned NOT NULL AUTO_INCREMENT,`system` int(10) unsigned NOT NULL,`name` varchar(255) NOT NULL,PRIMARY KEY (`id`)) ENGINE=InnoDB COLLATE='utf8_general_ci' CHARSET=utf8;

DROP TABLE IF EXISTS `system`;
CREATE TABLE IF NOT EXISTS `system` (`id` int(10) unsigned NOT NULL AUTO_INCREMENT,`name` varchar(255) NOT NULL,PRIMARY KEY (`id`)) ENGINE=InnoDB COLLATE='utf8_general_ci' CHARSET=utf8;
