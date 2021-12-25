-- phpMyAdmin SQL Dump
-- version 5.1.0
-- https://www.phpmyadmin.net/
--
-- Хост: 192.168.0.101:3306
-- Время создания: Дек 25 2021 г., 15:46
-- Версия сервера: 8.0.24
-- Версия PHP: 8.0.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `2.1`
--

-- --------------------------------------------------------

--
-- Структура таблицы `модель пам'яті`
--

CREATE TABLE `модель пам'яті` (
  `id` bigint UNSIGNED NOT NULL,
  `назва` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `довідник архітектур пк`
--

CREATE TABLE `довідник архітектур пк` (
  `id` bigint UNSIGNED NOT NULL,
  `назва` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- --------------------------------------------------------

--
-- Структура таблицы `довідник архітектур пк_компанія-розробник архітектури`
--

CREATE TABLE `довідник архітектур пк_компанія-розробник архітектури` (
  `id` bigint UNSIGNED NOT NULL,
  `id_довідник архітектур пк` bigint UNSIGNED DEFAULT NULL,
  `id_компанія-розробник архітектури` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- --------------------------------------------------------

--
-- Структура таблицы `компанія-розробник архітектури`
--

CREATE TABLE `компанія-розробник архітектури` (
  `id` bigint UNSIGNED NOT NULL,
  `назва` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- --------------------------------------------------------

--
-- Структура таблицы `компанія-розробник архітектури_сімейство архітектур`
--

CREATE TABLE `компанія-розробник архітектури_сімейство архітектур` (
  `id` bigint UNSIGNED NOT NULL,
  `id_компанія-розробник архітектури` bigint UNSIGNED DEFAULT NULL,
  `id_сімейство архітектур` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- --------------------------------------------------------

--
-- Структура таблицы `призначення`
--

CREATE TABLE `призначення` (
  `id` bigint UNSIGNED NOT NULL,
  `призначення` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `процессорна архітектура`
--

CREATE TABLE `процессорна архітектура` (
  `id` bigint UNSIGNED NOT NULL,
  `назва` varchar(20) NOT NULL,
  `розрядність` tinyint NOT NULL,
  `максимальна адреса віртуальної пам'яті` bigint NOT NULL,
  `многопоточність` tinyint(1) NOT NULL,
  `многопроцессорність` tinyint(1) NOT NULL,
  `наявність L3 кешу` tinyint(1) NOT NULL,
  `наявність L2 кешу` tinyint(1) NOT NULL,
  `багаточіплетність` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- --------------------------------------------------------

--
-- Структура таблицы `процессорна архітектура_регістр`
--

CREATE TABLE `процессорна архітектура_регістр` (
  `id` bigint UNSIGNED NOT NULL,
  `id_процессорна архітектура` bigint UNSIGNED DEFAULT NULL,
  `id_регістр` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `процессорна архітектура_інструкція`
--

CREATE TABLE `процессорна архітектура_інструкція` (
  `id` tinyint(1) NOT NULL,
  `id_процессорна архітектура` bigint UNSIGNED DEFAULT NULL,
  `id_інструкція` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `регістр`
--

CREATE TABLE `регістр` (
  `id` bigint UNSIGNED NOT NULL,
  `назва` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `регістр_призначення`
--

CREATE TABLE `регістр_призначення` (
  `id` bigint UNSIGNED NOT NULL,
  `id_регістр` bigint UNSIGNED DEFAULT NULL,
  `id_призначення` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `регістр_тип`
--

CREATE TABLE `регістр_тип` (
  `id` bigint UNSIGNED NOT NULL,
  `id_регістр` bigint UNSIGNED DEFAULT NULL,
  `id_тип` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `режим роботи`
--

CREATE TABLE `режим роботи` (
  `id` bigint UNSIGNED NOT NULL,
  `назва` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- --------------------------------------------------------

--
-- Структура таблицы `сімейство архітектур`
--

CREATE TABLE `сімейство архітектур` (
  `id` bigint UNSIGNED NOT NULL,
  `назва` varchar(20) NOT NULL,
  `порядок слідування байтів` varchar(20) NOT NULL,
  `скалярність` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- --------------------------------------------------------

--
-- Структура таблицы `сімейство архітектур_модель пам'яті`
--

CREATE TABLE `сімейство архітектур_модель пам'яті` (
  `id` bigint UNSIGNED NOT NULL,
  `id_сімейство архітектур` bigint UNSIGNED DEFAULT NULL,
  `id_модель пам'яті` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `сімейство архітектур_процессорна архітектура`
--

CREATE TABLE `сімейство архітектур_процессорна архітектура` (
  `id` bigint UNSIGNED NOT NULL,
  `id_сімейство архітектур` bigint UNSIGNED DEFAULT NULL,
  `id_процессорна архітектура` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- --------------------------------------------------------

--
-- Структура таблицы `сімейство архітектур_режим роботи`
--

CREATE TABLE `сімейство архітектур_режим роботи` (
  `id` bigint UNSIGNED NOT NULL,
  `id_сімейство архітектур` bigint UNSIGNED DEFAULT NULL,
  `id_режим роботи` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- --------------------------------------------------------

--
-- Структура таблицы `тип`
--

CREATE TABLE `тип` (
  `id` bigint UNSIGNED NOT NULL,
  `тип` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `інструкція`
--

CREATE TABLE `інструкція` (
  `id` bigint UNSIGNED NOT NULL,
  `назва` varchar(20) NOT NULL,
  `розрядність` smallint NOT NULL,
  `SIMD` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



-- --------------------------------------------------------

--
-- Структура таблицы `інструкція_призначення`
--

CREATE TABLE `інструкція_призначення` (
  `id` bigint UNSIGNED NOT NULL,
  `id_інструкція` bigint UNSIGNED DEFAULT NULL,
  `id_призначенння` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `модель пам'яті`
--
ALTER TABLE `модель пам'яті`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `довідник архітектур пк`
--
ALTER TABLE `довідник архітектур пк`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `довідник архітектур пк_компанія-розробник архітектури`
--
ALTER TABLE `довідник архітектур пк_компанія-розробник архітектури`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `relation_row_unique` (`id_довідник архітектур пк`,`id_компанія-розробник архітектури`),
  ADD KEY `id_довідник` (`id_довідник архітектур пк`),
  ADD KEY `id_компанія` (`id_компанія-розробник архітектури`);

--
-- Индексы таблицы `компанія-розробник архітектури`
--
ALTER TABLE `компанія-розробник архітектури`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `компанія-розробник архітектури_сімейство архітектур`
--
ALTER TABLE `компанія-розробник архітектури_сімейство архітектур`
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `relation_row_unique` (`id_компанія-розробник архітектури`,`id_сімейство архітектур`),
  ADD KEY `id_компанія` (`id_компанія-розробник архітектури`),
  ADD KEY `id_сімейство` (`id_сімейство архітектур`);

--
-- Индексы таблицы `призначення`
--
ALTER TABLE `призначення`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `процессорна архітектура`
--
ALTER TABLE `процессорна архітектура`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `процессорна архітектура_регістр`
--
ALTER TABLE `процессорна архітектура_регістр`
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `relation_row_unique` (`id_процессорна архітектура`,`id_регістр`),
  ADD KEY `id_архітектура` (`id_процессорна архітектура`),
  ADD KEY `id_регістр` (`id_регістр`);

--
-- Индексы таблицы `процессорна архітектура_інструкція`
--
ALTER TABLE `процессорна архітектура_інструкція`
  ADD UNIQUE KEY `relation_row_unique` (`id_процессорна архітектура`,`id_інструкція`),
  ADD KEY `id_архітектура` (`id_процессорна архітектура`),
  ADD KEY `id_інструкція` (`id_інструкція`);

--
-- Индексы таблицы `регістр`
--
ALTER TABLE `регістр`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `регістр_призначення`
--
ALTER TABLE `регістр_призначення`
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `relation_row_unique` (`id_регістр`,`id_призначення`),
  ADD KEY `id_призначення` (`id_призначення`),
  ADD KEY `id_регістр` (`id_регістр`);

--
-- Индексы таблицы `регістр_тип`
--
ALTER TABLE `регістр_тип`
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `relation_row_unique` (`id_регістр`,`id_тип`),
  ADD KEY `id_регістр` (`id_регістр`),
  ADD KEY `id_тип` (`id_тип`);

--
-- Индексы таблицы `режим роботи`
--
ALTER TABLE `режим роботи`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `сімейство архітектур`
--
ALTER TABLE `сімейство архітектур`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `сімейство архітектур_модель пам'яті`
--
ALTER TABLE `сімейство архітектур_модель пам'яті`
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `relation_row_unique` (`id_сімейство архітектур`,`id_модель пам'яті`),
  ADD KEY `id_сімейство` (`id_сімейство архітектур`),
  ADD KEY `id_модель` (`id_модель пам'яті`);

--
-- Индексы таблицы `сімейство архітектур_процессорна архітектура`
--
ALTER TABLE `сімейство архітектур_процессорна архітектура`
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `relation_row_unique` (`id_сімейство архітектур`,`id_процессорна архітектура`),
  ADD KEY `id_сімейство` (`id_сімейство архітектур`),
  ADD KEY `id_архітектура` (`id_процессорна архітектура`);

--
-- Индексы таблицы `сімейство архітектур_режим роботи`
--
ALTER TABLE `сімейство архітектур_режим роботи`
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `relation_row_unique` (`id_сімейство архітектур`,`id_режим роботи`),
  ADD KEY `id_сімейство` (`id_сімейство архітектур`),
  ADD KEY `id_режим` (`id_режим роботи`);

--
-- Индексы таблицы `тип`
--
ALTER TABLE `тип`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `інструкція`
--
ALTER TABLE `інструкція`
  ADD UNIQUE KEY `id` (`id`);

--
-- Индексы таблицы `інструкція_призначення`
--
ALTER TABLE `інструкція_призначення`
  ADD UNIQUE KEY `id` (`id`),
  ADD UNIQUE KEY `relation_row_unique` (`id_інструкція`,`id_призначенння`),
  ADD KEY `id_інструкція` (`id_інструкція`),
  ADD KEY `id_призначенння` (`id_призначенння`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `модель пам'яті`
--
ALTER TABLE `модель пам'яті`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT для таблицы `довідник архітектур пк`
--
ALTER TABLE `довідник архітектур пк`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- AUTO_INCREMENT для таблицы `довідник архітектур пк_компанія-розробник архітектури`
--
ALTER TABLE `довідник архітектур пк_компанія-розробник архітектури`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT для таблицы `компанія-розробник архітектури`
--
ALTER TABLE `компанія-розробник архітектури`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT для таблицы `компанія-розробник архітектури_сімейство архітектур`
--
ALTER TABLE `компанія-розробник архітектури_сімейство архітектур`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT для таблицы `призначення`
--
ALTER TABLE `призначення`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `процессорна архітектура`
--
ALTER TABLE `процессорна архітектура`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;

--
-- AUTO_INCREMENT для таблицы `процессорна архітектура_регістр`
--
ALTER TABLE `процессорна архітектура_регістр`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `регістр`
--
ALTER TABLE `регістр`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `регістр_призначення`
--
ALTER TABLE `регістр_призначення`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `регістр_тип`
--
ALTER TABLE `регістр_тип`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `режим роботи`
--
ALTER TABLE `режим роботи`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT для таблицы `сімейство архітектур`
--
ALTER TABLE `сімейство архітектур`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT для таблицы `сімейство архітектур_модель пам'яті`
--
ALTER TABLE `сімейство архітектур_модель пам'яті`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT для таблицы `сімейство архітектур_процессорна архітектура`
--
ALTER TABLE `сімейство архітектур_процессорна архітектура`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT для таблицы `сімейство архітектур_режим роботи`
--
ALTER TABLE `сімейство архітектур_режим роботи`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT для таблицы `тип`
--
ALTER TABLE `тип`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `інструкція`
--
ALTER TABLE `інструкція`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT для таблицы `інструкція_призначення`
--
ALTER TABLE `інструкція_призначення`
  MODIFY `id` bigint UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `довідник архітектур пк_компанія-розробник архітектури`
--
ALTER TABLE `довідник архітектур пк_компанія-розробник архітектури`
  ADD CONSTRAINT `довідник архітектур пк_компанія-розробник архітектури_ibfk_1` FOREIGN KEY (`id_довідник архітектур пк`) REFERENCES `довідник архітектур пк` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `довідник архітектур пк_компанія-розробник архітектури_ibfk_2` FOREIGN KEY (`id_компанія-розробник архітектури`) REFERENCES `компанія-розробник архітектури` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `компанія-розробник архітектури_сімейство архітектур`
--
ALTER TABLE `компанія-розробник архітектури_сімейство архітектур`
  ADD CONSTRAINT `компанія-розробник архітектури_сімейство архітектур_ibfk_1` FOREIGN KEY (`id_компанія-розробник архітектури`) REFERENCES `компанія-розробник архітектури` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `компанія-розробник архітектури_сімейство архітектур_ibfk_2` FOREIGN KEY (`id_сімейство архітектур`) REFERENCES `сімейство архітектур` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `процессорна архітектура_регістр`
--
ALTER TABLE `процессорна архітектура_регістр`
  ADD CONSTRAINT `процессорна архітектура_регістр_ibfk_1` FOREIGN KEY (`id_процессорна архітектура`) REFERENCES `процессорна архітектура` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `процессорна архітектура_регістр_ibfk_2` FOREIGN KEY (`id_регістр`) REFERENCES `регістр` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `процессорна архітектура_інструкція`
--
ALTER TABLE `процессорна архітектура_інструкція`
  ADD CONSTRAINT `процессорна архітектура_інструкція_ibfk_1` FOREIGN KEY (`id_процессорна архітектура`) REFERENCES `процессорна архітектура` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `процессорна архітектура_інструкція_ibfk_2` FOREIGN KEY (`id_інструкція`) REFERENCES `інструкція` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `регістр_призначення`
--
ALTER TABLE `регістр_призначення`
  ADD CONSTRAINT `регістр_призначення_ibfk_1` FOREIGN KEY (`id_призначення`) REFERENCES `призначення` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `регістр_призначення_ibfk_2` FOREIGN KEY (`id_регістр`) REFERENCES `регістр` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `регістр_тип`
--
ALTER TABLE `регістр_тип`
  ADD CONSTRAINT `регістр_тип_ibfk_1` FOREIGN KEY (`id_регістр`) REFERENCES `регістр` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `регістр_тип_ibfk_2` FOREIGN KEY (`id_тип`) REFERENCES `тип` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `сімейство архітектур_модель пам'яті`
--
ALTER TABLE `сімейство архітектур_модель пам'яті`
  ADD CONSTRAINT `сімейство архітектур_модель пам'яті_ibfk_1` FOREIGN KEY (`id_сімейство архітектур`) REFERENCES `сімейство архітектур` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `сімейство архітектур_модель пам'яті_ibfk_2` FOREIGN KEY (`id_модель пам'яті`) REFERENCES `модель пам'яті` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `сімейство архітектур_процессорна архітектура`
--
ALTER TABLE `сімейство архітектур_процессорна архітектура`
  ADD CONSTRAINT `сімейство архітектур_процессорна архітектура_ibfk_1` FOREIGN KEY (`id_сімейство архітектур`) REFERENCES `сімейство архітектур` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `сімейство архітектур_процессорна архітектура_ibfk_2` FOREIGN KEY (`id_процессорна архітектура`) REFERENCES `процессорна архітектура` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `сімейство архітектур_режим роботи`
--
ALTER TABLE `сімейство архітектур_режим роботи`
  ADD CONSTRAINT `сімейство архітектур_режим роботи_ibfk_1` FOREIGN KEY (`id_сімейство архітектур`) REFERENCES `сімейство архітектур` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `сімейство архітектур_режим роботи_ibfk_2` FOREIGN KEY (`id_режим роботи`) REFERENCES `режим роботи` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `інструкція_призначення`
--
ALTER TABLE `інструкція_призначення`
  ADD CONSTRAINT `інструкція_призначення_ibfk_1` FOREIGN KEY (`id_інструкція`) REFERENCES `інструкція` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `інструкція_призначення_ibfk_2` FOREIGN KEY (`id_призначенння`) REFERENCES `призначення` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
